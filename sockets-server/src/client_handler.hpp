// client_handler.h
#pragma once

#include <winsock2.h>

void HandleClient(SOCKET clientSocket, int connectionTimeout);
