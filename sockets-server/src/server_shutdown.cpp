// server_shutdown.cpp

#include <windows.h>

#include <condition_variable>
#include <csignal>
#include <iostream>
#include <mutex>

#include "logging.hpp"
#include "server_shutdown.hpp"

bool g_shouldShutdown = false;

BOOL WINAPI ConsoleHandler(DWORD signal)
{
    if (!g_shouldShutdown && signal == CTRL_C_EVENT)
    {
        LogMessage("Ctrl-C received. Shutting down...");
        g_shouldShutdown = true;
    }

    return TRUE;
}

void SetShutdownHandler()
{
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);
}
