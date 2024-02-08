// config.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "logging.hpp"
#include "config.hpp"

Config::Config() : port(8888), threadPoolSize(4), connectionAcceptTimeout(1000)
{
    // Initialize with default values
}

bool Config::LoadFromConfigFile(const std::string &configFile)
{
    std::ifstream file(configFile);
    if (!file.is_open())
    {
        LogError("Failed to open configuration file: " + configFile);
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            if (key == "port")
            {
                port = std::stoi(value);
            }
            else if (key == "threadPoolSize")
            {
                threadPoolSize = std::stoi(value);
            }
            else if (key == "connectionAcceptTimeout")
            {
                connectionAcceptTimeout = std::stoi(value);
            }
            else if (key == "connectionTimeout")
            {
                connectionTimeout = std::stoi(value);
            }
        }
    }

    return true;
}
