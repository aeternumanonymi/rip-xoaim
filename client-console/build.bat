@echo off
setlocal enabledelayedexpansion

@RD /S /Q "%~dp0\bin"
mkdir "bin"

echo Starting build...
g++ -std=c++20 -m64 "src\main.cpp" -o "bin\console.exe" -lws2_32 -lole32
echo Build finished...

endlocal