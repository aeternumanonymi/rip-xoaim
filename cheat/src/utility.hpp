// utility.hpp

#ifndef UTILITY_H
#define UTILITY_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include <dynamic_import.hpp>
#include <xorstr.hpp>

class c_utility
{
public:
    static bool read_data_from_file(const std::string &file_path, std::vector<uint8_t> *raw_data);
    static DWORD calculate_volume_level(uint32_t percentage);
    static bool play_sound(const std::vector<uint8_t> &audio_data, uint32_t volume_percentage);
    static int execute_with_arguments(const std::string &exe_path, const std::string &arguments);
    static bool create_temp_folder(std::string *created_path);
    static bool delete_directory(const std::string &path);
};

#endif
