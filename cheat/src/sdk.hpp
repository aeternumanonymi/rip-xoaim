#ifndef SDK_HPP
#define SDK_HPP

#include "utlthash.hpp"

class CSchemaField
{
public:
    std::string GetName()
    {
        uintptr_t address = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this), &address, sizeof(uintptr_t))))
        {
            return "";
        }

        char str_buffer[128];
        if (!nt::success(g_process.read_memory(address, str_buffer, sizeof(str_buffer) - 1)))
        {
            return "";
        }

        str_buffer[127] = '\0';
        return std::string(str_buffer);
    }

    std::uint32_t GetOffset()
    {
        uint32_t offset = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x10, &offset, sizeof(uint32_t))))
        {
            return 0;
        }

        return offset;
    }
};

class CSchemaClassBindingBase
{
public:
    std::string GetName()
    {
        uintptr_t address = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x8, &address, sizeof(address))))
        {
            return "";
        }

        char str_buffer[128];
        if (!nt::success(g_process.read_memory(address, str_buffer, sizeof(str_buffer) - 1)))
        {
            return "";
        }

        str_buffer[127] = '\0';
        return std::string(str_buffer);
    }

    std::string GetProjectName()
    {
        char str_buffer[128];
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x10, str_buffer, sizeof(str_buffer) - 1)))
        {
            return "";
        }

        str_buffer[127] = '\0';
        return std::string(str_buffer);
    }

    std::uint32_t GetSize()
    {
        uint32_t size = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x18, &size, sizeof(uint32_t))))
        {
            return 0;
        }

        return size;
    }

    std::uint16_t GetNumFields()
    {
        uint16_t count = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x1C, &count, sizeof(uint16_t))))
        {
            return 0;
        }

        return count;
    }

    CSchemaField *GetFields()
    {
        uintptr_t fields_address = 0;
        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x28, &fields_address, sizeof(uintptr_t))))
        {
            return nullptr;
        }

        return reinterpret_cast<CSchemaField *>(fields_address);
    }
};

class CSchemaSystemTypeScope
{
public:
    CUtlTSHash<CSchemaClassBindingBase *, 256, unsigned int> GetBindingsTable()
    {
        CUtlTSHash<CSchemaClassBindingBase *, 256, unsigned int> table;

        if (!nt::success(g_process.read_memory(reinterpret_cast<uintptr_t>(this) + 0x588, &table, sizeof(table))))
        {
            return {};
        }

        return table;
    };
};

#endif