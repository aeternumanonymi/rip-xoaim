// cheat.cpp

#include <thread>
#include <math.hpp>

#include "cheat.hpp"
#include "utility.hpp"
#include "kv3-parser.hpp"
#include "netvars.hpp"
#include "vischeck.hpp"
#include "entities.hpp"
#include "aimbot.hpp"

remote_process g_process;
c_entities g_entities;
c_netvars g_netvars;
c_vischeck g_vischeck;
c_aimbot g_aimbot;

#ifdef DEBUG_BUILD
c_overlay g_overlay;
#endif

void c_cheat::execute(HINSTANCE instance, INT cmd_show)
{
    wait_for_initialize_process();
    printf(xors("Process initialized...\n"));

    if (!g_netvars.initialize() || !g_netvars.process())
    {
        printf(xors("Failed to initialize netvars...\n"));
    }

    printf(xors("Netvars initialized...\n"));

    if (!g_vischeck.initialize(xors("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Counter-Strike Global Offensive\\game\\csgo\\maps"), xors("de_dust2")))
    {
        printf(xors("Failed to initialize vischeck...\n"));
    }

    printf(xors("Vischeck initialized...\n"));

    if (!g_entities.initialize())
    {
        printf(xors("Failed to initialize entity cache...\n"));
    }

    printf(xors("Entity cache initialized...\n"));

#ifdef DEBUG_BUILD
    if (!g_overlay.initialize(instance, cmd_show))
    {
        printf(xors("Failed to initialize overlay...\n"));
    }

    printf(xors("Overlay initialized...\n"));
#endif

    std::vector<uint8_t> audio_data;
    if (c_utility::read_data_from_file(xors("..\\assets\\initialized.wav"), &audio_data))
    {
        c_utility::play_sound(audio_data, 25);
    }

    for (;;)
    {
        if (GetAsyncKeyState(VK_DELETE) & 0x8000)
        {
            break;
        }

        if (g_entities.update())
        {

#ifdef DEBUG_BUILD
            g_aimbot.execute();
            g_overlay.execute();
#endif
        }

        m_bunnyhop.execute();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void c_cheat::wait_for_initialize_process()
{
    for (;;)
    {
        if (g_process.initialize(xors("cs2.exe")) && g_process.open())
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for (;;)
    {
        uintptr_t a;
        size_t b;

        if (g_process.get_module_information(xors("matchmaking.dll"), &a, &b))
        {
            break;
        }
    }
}