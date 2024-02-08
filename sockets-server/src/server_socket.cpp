// server_socket.cpp

#include <stdexcept>

#include "server_socket.hpp"
#include "logging.hpp"

ServerSocket::ServerSocket() : m_socket(INVALID_SOCKET)
{
    // Initialize with invalid socket
}

ServerSocket::~ServerSocket()
{
    Close();
}

bool ServerSocket::Initialize()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("WSAStartup failed.");
    }

    return true;
}

bool ServerSocket::Bind(int port)
{
    m_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET)
    {
        throw std::runtime_error("Error creating server socket.");
    }

    sockaddr_in6 serverAddress = {};
    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_port = htons(port);
    serverAddress.sin6_addr = in6addr_any;

    if (bind(m_socket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error binding to port.");
    }

    return true;
}

bool ServerSocket::Listen()
{
    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error listening.");
    }

    return true;
}

SOCKET ServerSocket::AcceptWithTimeout(int timeout)
{
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(m_socket, &readSet);

    timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    int selectResult = select(static_cast<int>(m_socket) + 1, &readSet, nullptr, nullptr, &tv);
    if (selectResult > 0 && FD_ISSET(m_socket, &readSet))
    {
        SOCKET clientSocket = accept(m_socket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET)
        {
            LogError("Error accepting client connection...");
        }
        return clientSocket;
    }
    else if (selectResult == 0)
    {
        return INVALID_SOCKET;
    }
    else
    {
        LogError("Error in select() function...");
        return INVALID_SOCKET;
    }
}

void ServerSocket::Close()
{
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}
