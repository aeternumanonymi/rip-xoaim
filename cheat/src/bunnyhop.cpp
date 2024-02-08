// bunnyhop.cpp

#include <thread>

#include "entities.hpp"
#include "bunnyhop.hpp"

extern c_entities g_entities;

void c_bunnyhop::execute()
{
    /*
    if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000 && g_entities.m_local_player.flags & FL_ONGROUND)
    {
        send_input(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        send_input(false);
    }
    */
}

void c_bunnyhop::send_input(bool key_down)
{
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = key_down ? KEYEVENTF_SCANCODE : KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
    input.ki.wScan = MapVirtualKey(VK_SPACE, 0);
    SendInput(1, &input, sizeof(input));
}