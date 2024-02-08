@echo off
setlocal enabledelayedexpansion

@RD /S /Q "%~dp0\bin"
mkdir bin

set SOURCE_FILES=src\client_handler.cpp
set SOURCE_FILES=!SOURCE_FILES! src\config.cpp
set SOURCE_FILES=!SOURCE_FILES! src\logging.cpp
set SOURCE_FILES=!SOURCE_FILES! src\server_shutdown.cpp
set SOURCE_FILES=!SOURCE_FILES! src\server_socket.cpp
set SOURCE_FILES=!SOURCE_FILES! src\thread_pool.cpp
set SOURCE_FILES=!SOURCE_FILES! src\main.cpp

echo Starting build...
g++ -std=c++20 -m64 %SOURCE_FILES% -o "bin/sockets-server.exe" -lws2_32 -lpthread
echo Build finished

endlocal