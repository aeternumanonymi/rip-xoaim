@echo off
setlocal enabledelayedexpansion

@RD /S /Q "%~dp0\bin"
mkdir "bin"

echo Starting build...

set INCLUDE_PATHS=-I"C:\Work\xoaim\config\debug"
set INCLUDE_PATHS=!INCLUDE_PATHS! -I"C:\Work\xoaim\shared\include"
set INCLUDE_PATHS=!INCLUDE_PATHS! -I"C:\Work\xoaim\cheat\src\imgui"

set SOURCE_FILES=src\imgui\imgui.cpp 
set SOURCE_FILES=!SOURCE_FILES! src\imgui\imgui_impl_win32.cpp
set SOURCE_FILES=!SOURCE_FILES! src\imgui\imgui_widgets.cpp
set SOURCE_FILES=!SOURCE_FILES! src\imgui\imgui_impl_dx11.cpp
set SOURCE_FILES=!SOURCE_FILES! src\imgui\imgui_draw.cpp
set SOURCE_FILES=!SOURCE_FILES! src\imgui\imgui_tables.cpp
set SOURCE_FILES=!SOURCE_FILES! src\utility.cpp
set SOURCE_FILES=!SOURCE_FILES! src\kv3-parser.cpp
set SOURCE_FILES=!SOURCE_FILES! src\vischeck.cpp
set SOURCE_FILES=!SOURCE_FILES! src\netvars.cpp
set SOURCE_FILES=!SOURCE_FILES! src\entities.cpp
set SOURCE_FILES=!SOURCE_FILES! src\bunnyhop.cpp
set SOURCE_FILES=!SOURCE_FILES! src\aimbot.cpp
set SOURCE_FILES=!SOURCE_FILES! src\overlay.cpp
set SOURCE_FILES=!SOURCE_FILES! src\cheat.cpp
set SOURCE_FILES=!SOURCE_FILES! src\main.cpp

set LIBRARY_FILES=-ld3d11
SET LIBRARY_FILES=!LIBRARY_FILES! -ld3dcompiler
SET LIBRARY_FILES=!LIBRARY_FILES! -lgdi32
SET LIBRARY_FILES=!LIBRARY_FILES! -lwinmm
SET LIBRARY_FILES=!LIBRARY_FILES! -lole32
SET LIBRARY_FILES=!LIBRARY_FILES! -ldwmapi

g++ -std=c++20 -m64 -march=native %INCLUDE_PATHS% %SOURCE_FILES% -o "bin\cheat-debug.exe" %LIBRARY_FILES%

echo Build finished...

endlocal
