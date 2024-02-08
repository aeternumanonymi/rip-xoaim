// client_handler.cpp

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "client_handler.hpp"
#include "logging.hpp"

void HandleClient(SOCKET clientSocket, int connectionTimeout = 5000)
{
    constexpr int kBufferSize = 1024;
    char buffer[kBufferSize];

    try
    {
        if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&connectionTimeout), sizeof(connectionTimeout)) == SOCKET_ERROR)
        {
            throw std::runtime_error("Failed to set socket timeout...");
        }

        int bytesRead;
        while ((bytesRead = recv(clientSocket, buffer, kBufferSize, 0)) > 0)
        {
            buffer[bytesRead] = '\0';
            printf("Received: %s\n", std::string(buffer).c_str());

            const auto response = "Hello, client!";
            if (send(clientSocket, response, strlen(response), 0) == SOCKET_ERROR)
            {
                throw std::runtime_error("Failed to send data back to client...");
            }
        }
    }
    catch (const std::exception &e)
    {
        LogError("Exception: " + std::string(e.what()));
    }

    closesocket(clientSocket);
}
