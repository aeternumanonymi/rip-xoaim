// logging.cpp

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>

#include "logging.hpp"

std::ofstream g_logFile;
std::mutex g_logMutex;

void InitializeLogging()
{
    g_logFile.open("server_log.txt", std::ios_base::out | std::ios_base::app);
    if (!g_logFile.is_open())
    {
        throw std::runtime_error("Failed to open log file.");
    }
}

void LogMessage(const std::string &message)
{
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_logFile.is_open())
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_time = *std::localtime(&time);

        g_logFile << "[" << std::put_time(&tm_time, "%d.%m.%Y - %H:%M:%S") << "] " << message << std::endl;
    }
}

void LogError(const std::string &error)
{
    LogMessage("[ERROR] " + error);
}
