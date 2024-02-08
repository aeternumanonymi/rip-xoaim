// netsvars.hpp

#ifndef NETVARS_HPP
#define NETVARS_HPP

#include <unordered_map>

#include <process.hpp>
#include <fnv1a.hpp>

#include "sdk.hpp"

class c_netvars
{
public:
    c_netvars() = default;
    ~c_netvars() = default;

public:
    bool initialize();
    bool process();

public:
    uint32_t get_offset(const char *schema_field, const char *class_binding);

private:
    bool process_schema_system_signatures();
    bool process_client_signatures();

public:
    uintptr_t m_input = 0;
    uintptr_t m_view_angles = 0;
    uintptr_t m_view_matrix = 0;
    uintptr_t m_local_player = 0;
    uintptr_t m_entity_list = 0;

public:
    uintptr_t m_pGameSceneNode = 0;
    uintptr_t m_iHealth = 0;
    uintptr_t m_fFlags = 0;
    uintptr_t m_nSubclassID = 0;
    uintptr_t m_vecAbsOrigin = 0;
    uintptr_t m_bPawnIsAlive = 0;
    uintptr_t m_hPlayerPawn = 0;
    uintptr_t m_nodeToWorld = 0;
    uintptr_t m_lifeState = 0;
    uintptr_t m_iTeamNum = 0;
    uintptr_t m_vOldOrigin = 0;
    uintptr_t m_angEyeAngles = 0;
    uintptr_t m_vecLastClipCameraPos = 0;

private:
    std::unordered_map<fnv1a::hash_type, std::unordered_map<fnv1a::hash_type, uint32_t>> m_table_offsets;
    CSchemaSystemTypeScope *m_scope;
};

#endif