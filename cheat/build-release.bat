@echo off
setlocal enabledelayedexpansion

@RD /S /Q "%~dp0\bin"
mkdir "bin"

echo Starting build...

set INCLUDE_PATHS=-I"C:\Work\xoaim\config\release"
set INCLUDE_PATHS=!INCLUDE_PATHS! -I"C:\Work\xoaim\shared\include"

set SOURCE_FILES=src\utility.cpp
set SOURCE_FILES=!SOURCE_FILES! src\kv3-parser.cpp
set SOURCE_FILES=!SOURCE_FILES! src\vischeck.cpp
set SOURCE_FILES=!SOURCE_FILES! src\netvars.cpp
set SOURCE_FILES=!SOURCE_FILES! src\entities.cpp
set SOURCE_FILES=!SOURCE_FILES! src\bunnyhop.cpp
set SOURCE_FILES=!SOURCE_FILES! src\aimbot.cpp
set SOURCE_FILES=!SOURCE_FILES! src\cheat.cpp
set SOURCE_FILES=!SOURCE_FILES! src\main.cpp

SET LIBRARY_FILES=-lwinmm
SET LIBRARY_FILES=!LIBRARY_FILES! -lole32

g++ -std=c++20 -m64 -march=native %INCLUDE_PATHS% %SOURCE_FILES% -o "bin\cheat-release.exe" %LIBRARY_FILES%

echo Build finished...

endlocal
