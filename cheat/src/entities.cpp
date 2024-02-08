// entities.cpp

#include "entities.hpp"

bool c_entities::initialize()
{
    if (!g_process.get_module_information(xors("client.dll"), &m_client_module_base_address, &m_client_module_size) || !m_client_module_base_address || !m_client_module_size)
    {
        return false;
    }

    return true;
}

bool c_entities::update()
{
    if (!update_general())
    {
        return false;
    }

    if (!update_local_player())
    {
        return false;
    }

    if (!update_entities())
    {
        return false;
    }

    return true;
}

bool c_entities::world_to_screen(const math::vec3 &in, math::vec2 *out) const
{
    const auto w = m_view_matrix[3][0] * in.x + m_view_matrix[3][1] * in.y + m_view_matrix[3][2] * in.z + m_view_matrix[3][3];
    if (w < 0.001f)
        return false;

    const auto x = (m_view_matrix[0][0] * in.x + m_view_matrix[0][1] * in.y + m_view_matrix[0][2] * in.z + m_view_matrix[0][3]) / w;
    const auto y = (m_view_matrix[1][0] * in.x + m_view_matrix[1][1] * in.y + m_view_matrix[1][2] * in.z + m_view_matrix[1][3]) / w;

    std::int32_t screen_width = 1920;  // TODO: Change hardcoded resolution
    std::int32_t screen_height = 1080; // TODO: Change hardcoded resolution

    out->x = (screen_width / 2.0f) + (x * screen_width) / 2.0f;
    out->y = (screen_height / 2.0f) - (y * screen_height) / 2.0f;

    return true;
}

bool c_entities::update_general()
{
    if (!update_value(m_client_module_base_address + g_netvars.m_view_matrix, &m_view_matrix))
    {
        return false;
    }

    if (!update_value(m_client_module_base_address + g_netvars.m_input, &m_input, true))
    {
        return false;
    }

    if (!update_value(m_input + g_netvars.m_view_angles, &m_local_player_view_angles))
    {
        return false;
    }

    return true;
}

bool c_entities::update_local_player()
{
    if (!update_value(m_client_module_base_address + g_netvars.m_local_player, &m_local_player.base_address, true))
    {
        return false;
    }

    if (!update_value(m_local_player.base_address + g_netvars.m_hPlayerPawn, &m_local_player.player_pawn, true))
    {
        return false;
    }

    if (!update_value(m_client_module_base_address + 0X17ADAE0, &m_entity_list, true))
    {
        return false;
    }

    if (!update_value(m_entity_list + 0x8 * ((m_local_player.player_pawn & 0x7FFF) >> 9) + 16, &m_local_player.list_entry2, true))
    {
        return false;
    }

    // same
    if (!update_value(m_local_player.list_entry2 + 120 * (m_local_player.player_pawn & 0x1FF), &m_local_player.p_cs_player_pawn, true))
    {
        return false;
    }

    if (!update_value(m_entity_list + 0x10 + 8 * ((m_local_player.player_pawn & 0x7FFF) >> 9), &m_local_player.pawn_list_entry, true))
    {
        return false;
    }

    // same
    if (!update_value(m_local_player.pawn_list_entry + 0x78 * (m_local_player.player_pawn & 0x1FF), &m_local_player.pawn_address, true))
    {
        return false;
    }

    if (!update_value(m_local_player.pawn_address + g_netvars.m_vecLastClipCameraPos, &m_local_player.camera_position))
    {
        return false;
    }

    if (!update_value(m_local_player.p_cs_player_pawn + g_netvars.m_lifeState, &m_local_player.life_state))
    {
        return false;
    }

    if (!update_value(m_local_player.p_cs_player_pawn + g_netvars.m_fFlags, &m_local_player.flags))
    {
        return false;
    }

    if (!update_value(m_local_player.p_cs_player_pawn + g_netvars.m_vOldOrigin, &m_local_player.origin))
    {
        return false;
    }

    if (!update_value(m_local_player.base_address + g_netvars.m_iHealth, &m_local_player.health))
    {
        return false;
    }

    if (!update_value(m_local_player.base_address + g_netvars.m_iTeamNum, &m_local_player.team))
    {
        return false;
    }

    return true;
}

bool c_entities::update_entities()
{
    m_entities.clear();

    for (uint32_t index = 0; index < 32; index++)
    {
        entity_t entity = {};
        entity.index = index;

        if (!update_value(m_entity_list + (8 * (index & 0x7FFF) >> 9) + 16, &entity.list_entry, true))
        {
            continue;
        }

        if (!update_value(entity.list_entry + 120 * (index & 0x1FF), &entity.base_address, true))
        {
            continue;
        }

        if (!update_value(entity.base_address + g_netvars.m_hPlayerPawn, &entity.player_pawn, true))
        {
            continue;
        }

        if (!update_value(m_entity_list + 0x8 * ((entity.player_pawn & 0x7FFF) >> 9) + 16, &entity.list_entry2, true))
        {
            continue;
        }

        if (!update_value(entity.list_entry2 + 120 * (entity.player_pawn & 0x1FF), &entity.p_cs_player_pawn, true))
        {
            continue;
        }

        if (entity.p_cs_player_pawn == m_local_player.p_cs_player_pawn)
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + g_netvars.m_lifeState, &entity.life_state))
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + g_netvars.m_iHealth, &entity.health))
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + g_netvars.m_iTeamNum, &entity.team))
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + g_netvars.m_fFlags, &entity.flags))
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + g_netvars.m_vOldOrigin, &entity.origin))
        {
            continue;
        }

        if (!update_value(entity.p_cs_player_pawn + 0x310, &entity.game_scene, true))
        {
            continue;
        }

        if (!update_value(entity.game_scene + 0x160 + 0x80, &entity.bone_array, true))
        {
            continue;
        }

        if (!update_value(entity.bone_array + 6 * 32, &entity.head_bone))
        {
            continue;
        }

        m_entities.push_back(entity);
    }

    return true;
}

uintptr_t c_entities::get_entity(uintptr_t entity_list, uintptr_t previous_entry)
{
    uintptr_t list_entry = 0;
    if (previous_entry)
    {
        uintptr_t a;
        if (!nt::success(g_process.read_memory(previous_entry + 0x10, &a, sizeof(a))))
        {
            return 0;
        }

        if (!nt::success(g_process.read_memory(a + 0x60, &list_entry, sizeof(list_entry))))
        {
            return 0;
        }
    }
    else
    {
        if (!nt::success(g_process.read_memory(entity_list + 0x210, &list_entry, sizeof(list_entry))))
        {
            return 0;
        }
    }

    if (list_entry)
    {
        if (!nt::success(g_process.read_memory(list_entry, &list_entry, sizeof(list_entry))))
        {
            return 0;
        }

        return list_entry;
    }

    return 0;
}