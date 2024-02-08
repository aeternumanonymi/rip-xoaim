// main.cpp
#include "cheat.hpp"

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmd_line, INT cmd_show)
{
    c_cheat cheat;
    cheat.execute(instance, cmd_show);

    return 0;
}