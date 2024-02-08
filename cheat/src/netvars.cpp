// netvars.cpp

#include "netvars.hpp"

#include <util.hpp>

extern remote_process g_process;

bool c_netvars::initialize()
{
    if (!process_schema_system_signatures())
    {
        return false;
    }

    if (!process_client_signatures())
    {
        return false;
    }

    return true;
}

bool c_netvars::process()
{
    auto table = m_scope->GetBindingsTable();
    const auto elements = std::make_unique_for_overwrite<UtlTSHashHandle_t[]>(table.Count());
    const auto element_count = table.GetElements(0, table.Count(), elements.get());

    for (uint32_t element_index = 0; element_index < element_count; element_index++)
    {
        const auto element = elements[element_index];
        if (!element)
        {
            continue;
        }

        const auto class_binding = table.Element(element);
        if (!class_binding)
        {
            continue;
        }

        if (!class_binding->GetNumFields())
        {
            continue;
        }

        auto schema_field = &class_binding->GetFields()[0];
        if (!schema_field)
        {
            continue;
        }

        std::unordered_map<fnv1a::hash_type, std::uint32_t> offsets;
        for (uint32_t field_index = 0; field_index < class_binding->GetNumFields(); field_index++)
        {
            offsets.try_emplace(fnv1a_runtime(schema_field->GetName().c_str()), schema_field->GetOffset());
            schema_field = reinterpret_cast<CSchemaField *>(std::uintptr_t(schema_field) + 0x20);
        }

        m_table_offsets.try_emplace(fnv1a_runtime(class_binding->GetName().c_str()), offsets);
    }

    m_pGameSceneNode = get_offset(xors("C_BaseEntity"), xors("m_pGameSceneNode"));
    m_iHealth = get_offset(xors("C_BaseEntity"), xors("m_iHealth"));
    m_fFlags = get_offset(xors("C_BaseEntity"), xors("m_fFlags"));
    m_nSubclassID = get_offset(xors("C_BaseEntity"), xors("m_nSubclassID"));
    m_vecAbsOrigin = get_offset(xors("CGameSceneNode"), xors("m_vecAbsOrigin"));
    m_bPawnIsAlive = get_offset(xors("CCSPlayerController"), xors("m_bPawnIsAlive"));
    m_hPlayerPawn = get_offset(xors("CCSPlayerController"), xors("m_hPlayerPawn"));
    m_nodeToWorld = get_offset(xors("CGameSceneNode"), xors("m_nodeToWorld"));
    m_lifeState = get_offset(xors("C_BaseEntity"), xors("m_lifeState"));
    m_iTeamNum = get_offset(xors("BaseEntity"), xors("m_iTeamNum"));
    m_vOldOrigin = get_offset(xors("C_BasePlayerPawn"), xors("m_vOldOrigin"));
    m_angEyeAngles = get_offset(xors("C_CSPlayerPawnBase"), xors("m_angEyeAngles"));
    m_vecLastClipCameraPos = get_offset(xors("C_CSPlayerPawnBase"), xors("m_vecLastClipCameraPos"));

    return true;
}

uint32_t c_netvars::get_offset(const char *schema_field, const char *class_binding)
{
    return m_table_offsets[fnv1a_runtime(schema_field)][fnv1a_runtime(class_binding)];
}

bool c_netvars::process_schema_system_signatures()
{
    uintptr_t schema_system_module_base_address = 0;
    size_t schema_system_module_size = 0;

    if (!g_process.get_module_information(xors("schemasystem.dll"), &schema_system_module_base_address, &schema_system_module_size))
    {
        return false;
    }

    std::vector<uint8_t> schema_system_module_data(schema_system_module_size);
    if (!nt::success(g_process.read_memory(schema_system_module_base_address, schema_system_module_data.data(), schema_system_module_size)))
    {
        return false;
    }

    const auto base_interface_addr = util::find_pattern<uintptr_t>(schema_system_module_data.data(), schema_system_module_data.size(), xors("7C 0B 49 8B 80 ? ? ? ?"), 13, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::RIP_RELATIVE | sigscan_flags::SUBTRACT_START_ADDRESS);
    if (!base_interface_addr)
    {
        return false;
    }

    const auto list_element = util::find_pattern<uint32_t>(schema_system_module_data.data(), schema_system_module_data.size(), xors("0F B7 C8 48 8B 83 ? ? ? ?"), 6, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::DEREFERENCE);
    if (!list_element)
    {
        return false;
    }

    uintptr_t ptr_to_list_element = 0;
    if (!nt::success(g_process.read_memory(schema_system_module_base_address + base_interface_addr + list_element, &ptr_to_list_element, sizeof(uintptr_t))))
    {
        return false;
    }

    if (!nt::success(g_process.read_memory(ptr_to_list_element + (0x10 * 8), &m_scope, sizeof(uintptr_t))))
    {
        return false;
    }

    return true;
}

bool c_netvars::process_client_signatures()
{
    uintptr_t client_module_base_address = 0;
    size_t client_module_size = 0;

    if (!g_process.get_module_information(xors("client.dll"), &client_module_base_address, &client_module_size))
    {
        return false;
    }

    std::vector<uint8_t> client_module_data(client_module_size);
    if (!nt::success(g_process.read_memory(client_module_base_address, client_module_data.data(), client_module_size)))
    {
        return false;
    }

    m_input = util::find_pattern<uintptr_t>(client_module_data.data(), client_module_data.size(), xors("48 8B 0D ? ? ? ? 41 8B D5 4C 8B 09"), 0, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::RIP_RELATIVE | sigscan_flags::SUBTRACT_START_ADDRESS);
    if (!m_input)
    {
        return false;
    }

    m_view_angles = util::find_pattern<uint32_t>(client_module_data.data(), client_module_data.size(), xors("F2 0F 10 84 31 ? ? ? ?"), 5, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::DEREFERENCE);
    if (!m_view_angles)
    {
        return false;
    }

    m_view_matrix = util::find_pattern<uintptr_t>(client_module_data.data(), client_module_data.size(), xors("48 8D 0D ? ? ? ? 48 C1 E0 06"), 0, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::RIP_RELATIVE | sigscan_flags::SUBTRACT_START_ADDRESS);
    if (!m_view_matrix)
    {
        return false;
    }

    m_local_player = util::find_pattern<uintptr_t>(client_module_data.data(), client_module_data.size(), xors("48 8B 0D ? ? ? ? 48 85 C9 74 54 83 FF FF"), 0, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::RIP_RELATIVE | sigscan_flags::SUBTRACT_START_ADDRESS);
    if (!m_local_player)
    {
        return false;
    }

    // WRONG
    m_entity_list = util::find_pattern<uintptr_t>(client_module_data.data(), client_module_data.size(), xors("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 5C 24 ? 48 85 C0"), 0, sigscan_flags::PORTABLE_EXECUTABLE | sigscan_flags::RIP_RELATIVE | sigscan_flags::SUBTRACT_START_ADDRESS);
    if (!m_entity_list)
    {
        return false;
    }

    return true;
}