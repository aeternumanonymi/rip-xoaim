// logging.h
#pragma once

#include <string>

void InitializeLogging();
void LogMessage(const std::string& message);
void LogError(const std::string& error);
