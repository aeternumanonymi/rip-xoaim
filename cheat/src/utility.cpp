// utility.cpp

#include <thread>
#include <codecvt>
#include <locale>

#include "utility.hpp"

bool c_utility::read_data_from_file(const std::string &file_path, std::vector<uint8_t> *raw_data)
{
    const auto file = find_import_cached(CreateFileA)(file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
        DWORD file_size = find_import_inlined(GetFileSize)(file, NULL);
        raw_data->resize(file_size);

        DWORD bytes_read;
        if (find_import_cached(ReadFile)(file, raw_data->data(), file_size, &bytes_read, NULL))
        {
            find_import_inlined(CloseHandle)(file);
            return true;
        }

        find_import_inlined(CloseHandle)(file);
    }

    return false;
}

DWORD c_utility::calculate_volume_level(uint32_t percentage)
{
    WORD volumeLevel = static_cast<WORD>((static_cast<double>(percentage) / 100.0) * 0xFFFF);
    return (static_cast<DWORD>(volumeLevel) << 16) | static_cast<DWORD>(volumeLevel);
}

bool c_utility::play_sound(const std::vector<uint8_t> &audio_data, uint32_t volume_percentage)
{
    if (!waveOutGetNumDevs())
    {
        return false;
    }

    WAVEFORMATEX wave_format;
    wave_format.wFormatTag = WAVE_FORMAT_PCM;
    wave_format.nChannels = 2;
    wave_format.nSamplesPerSec = 44100;
    wave_format.nAvgBytesPerSec = 44100 * 2 * 2;
    wave_format.nBlockAlign = 4;
    wave_format.wBitsPerSample = 16;
    wave_format.cbSize = 0;

    std::vector<uint8_t> audio_buffer(audio_data.begin(), audio_data.end());
    HWAVEOUT wave_out;
    if (waveOutOpen(&wave_out, WAVE_MAPPER, &wave_format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
    {
        return false;
    }

    const auto volume_level = calculate_volume_level(25);
    if (waveOutSetVolume(wave_out, volume_level) != MMSYSERR_NOERROR)
    {
        std::cerr << "Error setting volume." << std::endl;
        waveOutClose(wave_out);
        return false;
    }

    WAVEHDR wave_header;
    ZeroMemory(&wave_header, sizeof(WAVEHDR));
    wave_header.lpData = reinterpret_cast<LPSTR>(audio_buffer.data());
    wave_header.dwBufferLength = audio_buffer.size();

    if (waveOutPrepareHeader(wave_out, &wave_header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
    {
        waveOutClose(wave_out);
        return false;
    }

    if (waveOutWrite(wave_out, &wave_header, sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
    {
        waveOutUnprepareHeader(wave_out, &wave_header, sizeof(WAVEHDR));
        waveOutClose(wave_out);
        return false;
    }

    while (true)
    {
        if (wave_header.dwFlags & WHDR_DONE)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    waveOutUnprepareHeader(wave_out, &wave_header, sizeof(WAVEHDR));
    waveOutClose(wave_out);

    return true;
}

int c_utility::execute_with_arguments(const std::string &exe_path, const std::string &arguments)
{
    std::string command = exe_path + " " + arguments;
    return system(command.c_str());
}

bool c_utility::create_temp_folder(std::string *created_path)
{
    wchar_t temp_path[MAX_PATH];
    DWORD result = GetTempPathW(MAX_PATH, temp_path);

    if (result == 0 || result > MAX_PATH)
    {
        return false;
    }

    GUID guid;
    if (CoCreateGuid(&guid) != S_OK)
    {
        return false;
    }

    wchar_t uuid[39];
    if (StringFromGUID2(guid, uuid, 39) == 0)
    {
        return false;
    }

    std::wstring temp_folder = temp_path;
    temp_folder += L"\\";
    temp_folder += uuid;

    if (!CreateDirectoryW(temp_folder.c_str(), nullptr))
    {
        return false;
    }

    auto wstringToString = [](const std::wstring &wstr)
    {
        return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wstr);
    };

    std::string multibyteStr = wstringToString(temp_folder);

    *created_path = multibyteStr;
    return true;
}

bool c_utility::delete_directory(const std::string &path)
{
    WIN32_FIND_DATAA find_data;
    HANDLE find = FindFirstFileA((path + "\\*").c_str(), &find_data);

    if (find == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    do
    {
        const std::string file_name = find_data.cFileName;
        if (file_name != "." && file_name != "..")
        {
            const std::string file_path = path + "\\" + file_name;

            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (!delete_directory(file_path))
                {
                    FindClose(find);
                    return false;
                }
            }
            else
            {
                if (!DeleteFileA(file_path.c_str()))
                {
                    FindClose(find);
                    return false;
                }
            }
        }
    } while (FindNextFileA(find, &find_data) != 0);

    FindClose(find);

    return RemoveDirectoryA(path.c_str()) != 0;
}