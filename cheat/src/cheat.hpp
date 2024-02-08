// cheat.hpp

#ifndef CHEAT_HPP
#define CHEAT_HPP

#include <process.hpp>
#include <config.hpp>

#include "bunnyhop.hpp"
#include "aimbot.hpp"

#ifdef DEBUG_BUILD
#include "overlay.hpp"
#endif

class c_cheat
{
public:
    c_cheat() = default;
    ~c_cheat() = default;

public:
    void execute(HINSTANCE instance, INT cmd_show);

private:
    void wait_for_initialize_process();

private:
    c_bunnyhop m_bunnyhop;
};

#endif