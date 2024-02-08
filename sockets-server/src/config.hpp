// config.h
#pragma once

#include <string>

struct Config {
    int port;
    int threadPoolSize;
    int connectionAcceptTimeout;
    int connectionTimeout;

    Config();
    bool LoadFromConfigFile(const std::string& configFile);
};
