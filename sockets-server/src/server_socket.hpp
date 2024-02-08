// server_socket.h
#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

class ServerSocket {
   public:
    ServerSocket();
    ~ServerSocket();

    bool Initialize();
    bool Bind(int port);
    bool Listen();

    SOCKET AcceptWithTimeout(int timeout);
    void Close();

   private:
    SOCKET m_socket;
};
