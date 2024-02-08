// config.hpp

#ifndef CONFIG_HPP
#define CONFIG_HPP

struct general_t
{
    bool toggle_key;
    bool exit_key;
    uint32_t notification_volume;
    bool aimbot;
    bool triggerbot;
    bool sound_esp;
    bool bunnyhop;
    bool autoknife;
    bool autostop;
    bool auotkill_blockers;
    bool disable_networking;
    bool load_config_from_file;
};

struct aimbot_t
{
    uint32_t key_bind1;
    uint32_t key_bind2;
    uint32_t disable_key;
    uint32_t smooth_percentage;
    bool off_target_application;
    bool head;
    bool body;
    bool arms;
    bool legs;
};

struct triggerbot_t
{
    uint32_t keybind1;
    uint32_t keybind2;
    uint32_t disable_key;
    bool head;
    bool body;
    bool arms;
    bool legs;
    uint32_t visibility_delay;
    uint32_t hitchance;
    uint32_t maximum_flash_alpha;
    bool local_player_on_groud;
    bool opposite_target_check;
    uint32_t minimum_delay;
    uint32_t maximum_delay;
}

struct sound_esp_t
{
    uint32_t key_bind1;
    uint32_t key_bind2;
    uint32_t disable_key;
    bool always_active;
    bool non_visible_players_only;
    uint32_t maximum_fov;
    uint32_t volume_level;
}

struct utility_t
{
    uint32_t bunnyhop_key;
    uint32_t autoknife_key;
    uint32_t autostop_key;
}

struct config_t
{
    general_t general;
    aimbot_t aimbot;
    triggerbot_t triggerbot;
    sound_esp_t sound_esp;
    utility_t utility;
};

class c_config
{
public:
    c_config::c_config() = default;
    c_config::~c_config() = default;

public:
    set_config(const config_t &config)
    {
        this->config = config;
    }

private:
    c_config m_config;
};

#endif