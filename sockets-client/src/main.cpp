#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

const auto ip = "::1";
const auto port = 8888;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed...\n");
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET6, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error creating client socket...\n");
        WSACleanup();
        return 1;
    }

    sockaddr_in6 serverAddress = {};
    serverAddress.sin6_family = AF_INET6;
    serverAddress.sin6_port = htons(port);
    inet_pton(AF_INET6, ip, &serverAddress.sin6_addr);

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("Error connecting to server...\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    constexpr int kBufferSize = 1024;
    char buffer[kBufferSize];
    int bytesRead = recv(clientSocket, buffer, kBufferSize, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Received from server: %s\n", buffer);
    } else {
        printf("Error receiving data from server...\n");
    }

    closesocket(clientSocket);
    WSACleanup();

    printf("Press any key to exit...\n");

    return _getwch();
}
