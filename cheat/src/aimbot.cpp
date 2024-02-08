// aimbot.cpp

#include "aimbot.hpp"

void c_aimbot::execute()
{
    filter_targets();
    update_valid_targets();

    if (condition_state() && GetAsyncKeyState(VK_LSHIFT) & 0x8000)
    {
        entity_t best_target = {};
        if (get_best_target(&best_target))
        {
            const auto target_angles = get_target_angles(best_target);
            const auto smoothed_angles = smooth_angles(target_angles, 0.666f);

            apply_aim(smoothed_angles);
        }
    }
}

void c_aimbot::filter_targets()
{
    for (const auto &entity : g_entities.m_entities)
    {
        if (entity.life_state != 256 || entity.health < 0 || entity.health > 100 || !is_visible(entity))
        {
            remove_target(entity.index);
        }
        else
        {
            create_target(entity);
        }
    }
}

void c_aimbot::update_valid_targets()
{
    for (auto &target : m_targets)
    {
        const auto end_time = std::chrono::steady_clock::now();
        target.visible_for_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - target.start_time).count();

        const auto target_angles = get_target_angles(target.entity);
        target.fov = get_angles_fov(target_angles);

        const auto it = std::find_if(m_targets.begin(), m_targets.end(), [target](const target_t &valid_target)
                                     { return valid_target.index == target.index; });

        if (it != m_targets.end())
        {
            const auto it = std::find_if(g_entities.m_entities.begin(), g_entities.m_entities.end(), [target](const entity_t &entity)
                                         { return entity.index == target.index; });

            target.entity = *it;
        }
    }
}

void c_aimbot::remove_target(uint32_t index)
{
    const auto it = std::find_if(
        m_targets.begin(), m_targets.end(), [index](const target_t &target)
        { return target.index == index; });

    if (it != m_targets.end())
    {
        m_targets.erase(it);
    }
}

void c_aimbot::create_target(entity_t entity)
{
    const auto visible = is_visible(entity);
    const auto it = std::find_if(
        m_targets.begin(), m_targets.end(),
        [entity](target_t target)
        { return target.index == entity.index; });

    if (it == m_targets.end())
    {
        target_t target = {};

        target.fov = 0.f;
        target.entity = entity;
        target.index = entity.index;
        target.visible_for_ms = 0;
        target.start_time = std::chrono::steady_clock::now();

        m_targets.push_back(target);
    }
}

bool c_aimbot::condition_state()
{
    if (g_entities.m_local_player.life_state != 256)
    {
        return false;
    }

    const auto health = g_entities.m_local_player.health;
    if (health < 1 && health > 100)
    {
        return false;
    }

    if (g_entities.m_local_player.flags != 65665) // not on ground (local/others have different flag values)
    {
        return false;
    }

    return true;
}

bool c_aimbot::get_best_target(entity_t *best_target)
{
    bool have_target = false;
    float smallest_fov = 999.f;

    for (const auto &entity : g_entities.m_entities)
    {
        if (!is_valid_target(entity))
        {
            continue;
        }

        const auto target_angles = get_target_angles(entity);
        const auto target_fov = get_angles_fov(target_angles);

        if (target_fov < smallest_fov)
        {
            smallest_fov = target_fov;
            *best_target = entity;
            have_target = true;
        }
    }

    return have_target;
}

bool c_aimbot::is_valid_target(const entity_t &target)
{
    if (target.life_state != 256)
    {
        return false;
    }

    if (target.health < 0 || target.health > 100)
    {
        return false;
    }

    if (target.flags != 65681) // not on ground (local/others have different flag values)
    {
        return false;
    }

    if (!is_visible(target))
    {
        return false;
    }

    const auto angles = get_target_angles(target);
    const auto fov = get_angles_fov(angles);

    if (fov > 30.f)
    {
        return false;
    }

    return true;
}

bool c_aimbot::is_visible(const entity_t &target)
{
    auto start = g_entities.m_local_player.origin;
    start.z += 70.f;

    return g_vischeck.is_visible(start, target.head_bone);
}

math::vec3 c_aimbot::get_target_angles(const entity_t &target)
{
    const auto position = target.head_bone - g_entities.m_local_player.camera_position;
    const auto distance = sqrt(pow(position.x, 2) + pow(position.y, 2));
    const auto pitch = -atan(position.z / distance) * 57.295779513 - g_entities.m_local_player_view_angles.x;
    const auto yaw = atan2f(position.y, position.x) * 57.295779513 - g_entities.m_local_player_view_angles.y;
    math::vec3 target_angles = {};

    target_angles.x = pitch;
    target_angles.y = yaw;

    return target_angles;
}

float c_aimbot::get_angles_fov(const math::vec3 &angles)
{
    return sqrt(pow(angles.y, 2) + pow(angles.x, 2));
}

math::vec3 c_aimbot::smooth_angles(const math::vec3 &angles, const float &amount)
{
    math::vec3 smoothed_angles = {};

    smoothed_angles.x = angles.x * (1.f - amount) + g_entities.m_local_player_view_angles.x;
    smoothed_angles.y = angles.y * (1.f - amount) + g_entities.m_local_player_view_angles.y;

    return smoothed_angles;
}

void c_aimbot::apply_aim(const math::vec3 &target_angles)
{
    g_process.write_memory(g_entities.m_input + g_netvars.m_view_angles, &target_angles, sizeof(target_angles));
}