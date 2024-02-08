// entities.hpp

#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <process.hpp>
#include <math.hpp>

#include "netvars.hpp"

extern remote_process g_process;
extern c_netvars g_netvars;

struct view_matrix_t
{
    const float *operator[](int index) const
    {
        return matrix[index];
    }

    float matrix[4][4];
};

struct local_player_t
{
    // Addresses
    uintptr_t base_address;
    uintptr_t player_pawn;
    uintptr_t list_entry2;
    uintptr_t p_cs_player_pawn;
    uintptr_t pawn_list_entry;
    uintptr_t pawn_address;

    // Values
    uint32_t life_state;
    uint32_t health;
    uint32_t team;
    uint32_t flags;
    math::vec3 origin;
    math::vec3 camera_position;
};

struct entity_t
{
    // Index
    uint32_t index;

    // Addresses
    uintptr_t list_entry;
    uintptr_t base_address;
    uintptr_t player_pawn;
    uintptr_t list_entry2;
    uintptr_t p_cs_player_pawn;

    // Values
    uint32_t life_state;
    uint32_t health;
    uint32_t team;
    uint32_t flags;
    uintptr_t game_scene;
    uintptr_t bone_array;
    math::vec3 origin;
    math::vec3 head_bone;
};

class c_entities
{
public:
    c_entities() = default;
    ~c_entities() = default;

public:
    bool initialize();
    bool update();
    bool world_to_screen(const math::vec3 &in, math::vec2 *out) const;

private:
    bool update_general();
    bool update_local_player();
    bool update_entities();

private:
    uintptr_t get_entity(uintptr_t entity_list, uintptr_t previous_entry);

private:
    template <typename Ty>
    bool update_value(uintptr_t address, Ty *value, bool validate_value = false)
    {
        return nt::success(g_process.read_memory(address, value, sizeof(Ty))) && (validate_value ? !!value : true);
    }

public:
    local_player_t m_local_player = {};
    std::vector<entity_t> m_entities;

    uintptr_t m_client_module_base_address = 0;
    size_t m_client_module_size = 0;
    math::vec3 m_local_player_view_angles;

    view_matrix_t m_view_matrix;
    uintptr_t m_entity_list = 0;
    uintptr_t m_input = 0;
};

#endif