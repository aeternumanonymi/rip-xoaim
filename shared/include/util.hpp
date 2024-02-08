// define util.hpp
#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdio>
#include <utility>
#include <stdexcept>
#include <fnv1a.hpp>
#include <xorstr.hpp>
#include <intrin.h>
#include <vector>
#include <filesystem>
#include <cctype>

#include "dynamic_import.hpp"

#define ENABLE_EXCEPTIONS 1
#define ENABLE_LOGGING 1

namespace
{
    // credits: learn_more (i think)
    template <typename T1, typename T2, typename T3>
    constexpr auto in_range(T1 x, T2 a, T3 b)
    {
        return ((x) >= a && (x) <= b);
    }

    template <typename T>
    constexpr auto get_bits(T x)
    {
        return (in_range((x), '0', '9') ? ((x) - '0') : (((x) & (~0x20)) - 'A' + 0xA));
    }

    template <typename T>
    constexpr auto get_byte(T x)
    {
        return (get_bits((x)[0]) << 4 | get_bits((x)[1]));
    }
}

namespace sigscan_flags
{
    const int PORTABLE_EXECUTABLE = 1 << 0;
    const int RIP_RELATIVE = 1 << 1;
    const int DEREFERENCE = 1 << 2;
    const int SUBTRACT_START_ADDRESS = 1 << 3;
}

namespace util
{

    template <typename... Args>
    constexpr __forceinline void log(const char *fmt, Args &&...args)
    {
        if constexpr (ENABLE_LOGGING == 1)
        {
            std::printf(fmt, std::forward<Args>(args)...);
        }
    }

    template <typename Ty>
    __forceinline void runtime_assert(const Ty condition, const char *message)
    {
        if (static_cast<bool>(condition) == false)
        {
            if constexpr (ENABLE_EXCEPTIONS == 1)
            {
                throw std::runtime_error(message);
            }
            else
            {
                std::abort();
            }

            if constexpr (ENABLE_LOGGING == 1)
            {
                ::util::log(xors("[!] runtime_assert failed: %s\n"), message);
            }
        }
    }

    inline void convert_wstring(const wchar_t *wstring, char *buffer)
    {
        size_t size_needed = std::wcstombs(nullptr, wstring, 0) + 1;
        std::wcstombs(buffer, wstring, size_needed);
    }

    inline void convert_string(const char *string, wchar_t *buffer)
    {
        size_t size_needed = std::mbstowcs(nullptr, string, 0) + 1;
        std::mbstowcs(buffer, string, size_needed);
    }

    inline void make_lowercase(char *str)
    {
        while (*str != '\0')
        {
            *str = std::tolower(*str);
            ++str;
        }
    }

    inline void *resolve_relative_call(const void *address, const std::uint32_t offset = 5) noexcept
    {
        const auto addr = reinterpret_cast<std::uintptr_t>(address);
        const auto displacement_value = *reinterpret_cast<std::int32_t *>(addr + 1);
        return reinterpret_cast<void *>(displacement_value + addr + offset);
    }

    inline std::vector<std::uint8_t> get_process_list()
    {
        const auto query = find_import_cached(NtQuerySystemInformation);

        while (true)
        {
            unsigned long len = 0;
            query(nt::SystemProcessInformation, nullptr, 0, &len);
            if (len <= 0)
            {
                util::log(xors("[-] Failed to get process list, NtQuerySystemInformation invalid buffer size.\n"));
                return {};
            }

            std::vector<std::uint8_t> result;
            result.resize(len);

            const auto status = query(nt::SystemProcessInformation, result.data(), len, &len);
            if (status == 0xC0000004 /*STATUS_INFO_LENGTH_MISMATCH*/)
            {
                continue;
            }

            if (!nt::success(status))
            {
                util::log(xors("[-] Failed to get process list, NtQuerySystemInformation failed with status 0x%lx\n"), status);
                break;
            }

            return std::move(result);
        }

        return {};
    }

    inline std::pair<void *, std::size_t> find_module(const fnv1a::hash_type module_name_hash)
    {
        for (auto it = static_cast<nt::LIST_ENTRY *>(nt::peb()->Ldr->InLoadOrderModuleList.Flink);
             it != &nt::peb()->Ldr->InLoadOrderModuleList;
             it = static_cast<nt::LIST_ENTRY *>(it->Flink))
        {
            const auto entry = reinterpret_cast<nt::LDR_DATA_TABLE_ENTRY *>(it);
            if (entry->DllBase && entry->BaseDllName.Buffer && entry->BaseDllName.Length && fnv1a_runtime(entry->BaseDllName.Buffer) == module_name_hash)
            {
                return {entry->DllBase, entry->SizeOfImage};
            }
        }

        return {};
    }

    inline void *find_export(const void *mod, const fnv1a::hash_type export_name_hash)
    {
        const auto pe = static_cast<const mapped_image *>(mod);
        const auto data_dir = pe->data_directory(nt::image_directory_entry_export);
        const auto exp_dir = reinterpret_cast<const nt::IMAGE_EXPORT_DIRECTORY *>(pe->as_uintptr() + data_dir->VirtualAddress);
        const auto names = reinterpret_cast<const std::uint32_t *>(pe->as_uintptr() + exp_dir->AddressOfNames);
        const auto funcs = reinterpret_cast<const std::uint32_t *>(pe->as_uintptr() + exp_dir->AddressOfFunctions);
        const auto ords = reinterpret_cast<const std::uint16_t *>(pe->as_uintptr() + exp_dir->AddressOfNameOrdinals);

        for (auto i = 0; i < exp_dir->NumberOfFunctions; ++i)
        {
            if (!names[i])
            {
                continue;
            }

            const auto name = pe->as<const char *>() + names[i];
            if (fnv1a_runtime(name) == export_name_hash)
            {
                return reinterpret_cast<void *>(pe->as_uintptr() + funcs[ords[i]]);
            }
        }

        return nullptr;
    }

    template <typename T = void *>
    inline T find_pattern(void *address, const std::size_t search_range, std::string_view pattern, const uint32_t offset, const uint32_t flags)
    {
        auto start = reinterpret_cast<std::uint8_t *>(address);
        const auto end = start + search_range - pattern.length();

        if (flags & sigscan_flags::PORTABLE_EXECUTABLE)
        {
            const auto pe = static_cast<mapped_image *>(address);
            const auto section_header = pe->section_header();
            for (std::uint16_t i = 0; i < pe->file_header()->NumberOfSections; ++i)
            {
                if (fnv1a_runtime(section_header[i].Name) == fnv1a_constexpr(".text"))
                {
                    start += section_header[i].VirtualAddress;
                    break;
                }
            }
        }

        for (auto iter = start; iter < end; ++iter)
        {
            uint8_t *temp_iter = iter;
            const char *temp_pat = pattern.data();

            bool found = true;

            while (*temp_pat != '\0')
            {
                if (*temp_pat == ' ')
                {
                    ++temp_pat;
                    continue;
                }

                if (*temp_pat == '\?')
                {
                    ++temp_iter;
                    ++temp_pat;
                    continue;
                }

                if (get_byte(temp_pat) == *temp_iter)
                {
                    ++temp_iter;
                    temp_pat += 2;
                    continue;
                }

                found = false;
                break;
            }

            if (found)
            {
                auto result_address = reinterpret_cast<uintptr_t>(iter) + offset;

                if (flags & sigscan_flags::RIP_RELATIVE)
                {
                    result_address = (result_address + 7 + *reinterpret_cast<uint32_t *>(result_address + 3));
                }

                if (flags & sigscan_flags::SUBTRACT_START_ADDRESS)
                {
                    result_address -= reinterpret_cast<uintptr_t>(address);
                }

                if constexpr (std::is_pointer<T>::value)
                {
                    return reinterpret_cast<T *>(result_address);
                }
                else
                {
                    if (flags & sigscan_flags::DEREFERENCE)
                    {
                        return *reinterpret_cast<T *>(result_address);
                    }
                    else
                    {
                        if constexpr (std::is_convertible_v<T, decltype(result_address)>)
                        {
                            return result_address;
                        }
                        else
                        {
                            return reinterpret_cast<T>(result_address);
                        }
                    }
                }
            }
        }

        return {};
    }
}

#endif