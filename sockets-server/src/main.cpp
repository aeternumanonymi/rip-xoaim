// server_main.cpp
#define WIN32_LEAN_AND_MEAN

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <thread>
#include <vector>

#include "client_handler.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "server_shutdown.hpp"
#include "server_socket.hpp"
#include "thread_pool.hpp"

bool InitializeServer()
{
    // Set shutdown handler
    SetShutdownHandler();

    return true;
}

int main()
{
    // Initialize logging
    InitializeLogging();

    // Load configuration from file
    Config config;
    if (!config.LoadFromConfigFile("../config/server_config.txt"))
    {
        LogError("Failed to load configuration...");
        return 1;
    }

    // Initialize server components
    if (!InitializeServer())
    {
        LogError("Server initialization failed...");
        return 1;
    }

    // Initialize server socket
    ServerSocket serverSocket;
    if (!serverSocket.Initialize() || !serverSocket.Bind(config.port) || !serverSocket.Listen())
    {
        LogError("Server setup failed...");
        serverSocket.Close();
        return 1;
    }

    // Initialize thread pool
    ThreadPool threadPool(config.threadPoolSize);

    // Accept and handle client connections
    while (!g_shouldShutdown)
    {
        SOCKET clientSocket = serverSocket.AcceptWithTimeout(config.connectionAcceptTimeout);
        if (clientSocket != INVALID_SOCKET)
        {
            threadPool.EnqueueTask([clientSocket, config]()
                                   { HandleClient(clientSocket, config.connectionTimeout); });
        }
    }

    // Clean up server resources
    serverSocket.Close();
    return 0;
}
