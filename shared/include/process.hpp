// process.hpp

#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <windef.h>

#include <dynamic_import.hpp>
#include <native.hpp>

#include "util.hpp"

class remote_process
{
public:
    remote_process(void) {}

    ~remote_process()
    {
        if (m_handle != nullptr)
        {
            find_import_inlined(NtClose)(m_handle);
        }
    }

    bool initialize(const char *process_name)
    {
        const auto process_list = util::get_process_list();
        util::runtime_assert(!process_list.empty(), xors("Failed to get process list.\n"));

        char process_name_copy[128] = {'\0'};
        strcpy(process_name_copy, process_name);
        util::make_lowercase(process_name_copy);

        auto iter = reinterpret_cast<const nt::SYSTEM_PROCESS_INFORMATION *>(process_list.data());

        do
        {
            if (iter->ImageName.Buffer && iter->ImageName.Buffer[0] != '\0')
            {
                char name[260] = {'\0'};
                util::convert_wstring(&iter->ImageName.Buffer[0], &name[0]);
                util::make_lowercase(name);

                if (!strcmp(process_name_copy, &name[0]))
                {
                    m_process_id = reinterpret_cast<uint64_t>(iter->UniqueProcessId);
                    return true;
                }
            }

            if (iter->NextEntryOffset == 0)
                break;

            *reinterpret_cast<const uint8_t **>(&iter) += iter->NextEntryOffset;
        } while (true);

        return false;
    }

    bool open()
    {
        nt::OBJECT_ATTRIBUTES attributes{};
        attributes.Length = sizeof(nt::OBJECT_ATTRIBUTES);

        nt::CLIENT_ID client_id{};
        client_id.UniqueProcess = reinterpret_cast<void *>(m_process_id);

        const auto status = find_import_inlined(NtOpenProcess)(&m_handle, PROCESS_ALL_ACCESS, &attributes, &client_id);
        return !status && nt::success(status) && m_handle != INVALID_HANDLE_VALUE;
    }

    template <typename Ty>
    __forceinline nt::NTSTATUS read_memory(const Ty address, void *buffer, ULONG size, PULONG num_bytes_read = nullptr) const noexcept
    {
        return find_import_cached(NtReadVirtualMemory)(this->get_handle(), (void *)address, buffer, size, num_bytes_read);
    }

    template <typename Ty>
    __forceinline nt::NTSTATUS write_memory(const Ty address, const void *buffer, ULONG size, PULONG num_bytes_written = nullptr) const noexcept
    {
        return find_import_cached(NtWriteVirtualMemory)(this->get_handle(), reinterpret_cast<void *>(address), const_cast<void *>(buffer), size, num_bytes_written);
    }

    __forceinline nt::NTSTATUS allocate_memory(void **buffer, SIZE_T size, ULONG type, ULONG protection) const noexcept
    {
        *buffer = 0;
        return find_import_cached(NtAllocateVirtualMemory)(this->get_handle(), buffer, 0, &size, type, protection);
    }

    template <typename Ty>
    __forceinline nt::NTSTATUS free_memory(const Ty address, ULONG free_type, SIZE_T size) const noexcept
    {
        return find_import_cached(NtFreeVirtualMemory)(this->get_handle(), (void **)(&address), &size, free_type);
    }

    template <typename Ty>
    __forceinline nt::NTSTATUS protect_memory(Ty address, SIZE_T size, ULONG new_protection, PULONG old_protection = nullptr) const noexcept
    {
        unsigned long old;
        const auto status = find_import_cached(NtProtectVirtualMemory)(this->get_handle(), reinterpret_cast<void **>(&address), &size, new_protection, &old);
        if (old_protection != nullptr)
        {
            *old_protection = old;
        }
        return status;
    }

    __forceinline nt::NTSTATUS query_info(const nt::PROCESSINFOCLASS info_class, void *buffer, ULONG size, PULONG ret_size = nullptr) const noexcept
    {
        return find_import_cached(NtQueryInformationProcess)(this->get_handle(), info_class, buffer, size, ret_size);
    }

    __forceinline bool get_module_information(const char *module_name, uintptr_t *base_address, size_t *module_size)
    {
        nt::PROCESS_BASIC_INFORMATION process_information;
        if (const auto status = this->query_info(nt::ProcessBasicInformation, &process_information, sizeof(process_information)); !nt::success(status))
        {
            util::log(xors("[-] Failed to get PROCESS_BASIC_INFORMATION: NtQueryInformationProcess failed with status 0x%lx\n"), status);
            return false;
        }

        nt::PEB64 peb;
        if (const auto status = this->read_memory(process_information.PebBaseAddress, &peb, sizeof(peb)); !nt::success(status))
        {
            util::log(xors("[-] Failed to read remote process PEB: NtReadVirtualMemory failed with status 0x%lx\n"), status);
            return false;
        }

        if (!peb.Ldr)
        {
            util::log(xors("[-] PEB.Ldr == null\n"));
            return false;
        }

        nt::PEB_LDR_DATA64 ldr_data;
        if (const auto status = this->read_memory(peb.Ldr, &ldr_data, sizeof(ldr_data)); !nt::success(status))
        {
            util::log(xors("[-] Failed to read remote process PEB_LDR_DATA: NtReadVirtualMemory failed with status 0x%lx\n"), status);
            return false;
        }

        auto *list_head = ldr_data.InLoadOrderModuleList.Flink;
        auto *iter = list_head;

        do
        {
            nt::LDR_DATA_TABLE_ENTRY64 table_entry;
            if (!nt::success(this->read_memory(iter, &table_entry, sizeof(table_entry))))
            {
                break;
            }

            iter = table_entry.InLoadOrderLinks.Flink;

            if (!table_entry.DllBase || !table_entry.SizeOfImage || !table_entry.BaseDllName.Buffer || !table_entry.BaseDllName.Length)
            {
                continue;
            }

            wchar_t dll_name_buffer[260] = {'\0'};
            if (!nt::success(this->read_memory(table_entry.BaseDllName.Buffer, &dll_name_buffer[0], table_entry.BaseDllName.Length)) || !dll_name_buffer[0])
            {
                continue;
            }

            char name[260] = {'\0'};
            util::convert_wstring(dll_name_buffer, name);
            util::make_lowercase(name);

            if (!strcmp(module_name, name))
            {
                *base_address = reinterpret_cast<uintptr_t>(table_entry.DllBase);
                *module_size = table_entry.SizeOfImage;

                return true;
            }
        } while (iter != list_head);

        return false;
    }

    __forceinline void *get_handle() const noexcept
    {
        return m_handle;
    }

    __forceinline uint32_t get_id() const noexcept
    {
        return m_process_id;
    }

private:
    void *m_handle;
    uint64_t m_process_id;
};

#endif