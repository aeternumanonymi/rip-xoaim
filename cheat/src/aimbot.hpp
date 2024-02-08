// aimbot.hpp

#ifndef AIMBOT_HPP
#define AIMBOT_HPP

#include "entities.hpp"
#include "vischeck.hpp"

#include <chrono>

extern c_entities g_entities;
extern c_vischeck g_vischeck;

struct target_t
{
    float fov;
    uint32_t index;
    uint32_t visible_for_ms;
    std::chrono::steady_clock::time_point start_time;
    entity_t entity;
};

class c_aimbot
{
public:
    void execute();

private:
    void filter_targets();
    void update_valid_targets();

private:
    void remove_target(uint32_t index);
    void create_target(entity_t entity);

private:
    void update_targets();
    bool condition_state();
    bool get_best_target(entity_t *best_target);
    bool is_valid_target(const entity_t &target);
    bool is_visible(const entity_t &target);
    math::vec3 get_target_angles(const entity_t &target);
    float get_angles_fov(const math::vec3 &angles);
    math::vec3 smooth_angles(const math::vec3 &angles, const float &amount);
    void apply_aim(const math::vec3 &target_angles);

public:
    std::vector<target_t> m_targets;
};

#endif