#include <iostream>
#include <windows.h>
#include <objbase.h>

#define DEBUG_BUILD

bool create_temp_folder(std::wstring *created_path)
{
    WCHAR temp_path[MAX_PATH];
    DWORD result = GetTempPathW(MAX_PATH, temp_path);

    if (result == 0 || result > MAX_PATH)
    {
        MessageBoxW(nullptr, L"Failed to get temporary path...", L"Error", MB_ICONERROR);
        return false;
    }

    GUID guid;
    if (CoCreateGuid(&guid) != S_OK)
    {
        MessageBoxW(nullptr, L"Failed to generate UUID", L"Error", MB_ICONERROR);
        return false;
    }

    WCHAR uuid[39];
    if (StringFromGUID2(guid, uuid, 39) == 0)
    {
        MessageBoxW(nullptr, L"Failed to convert UUID to string...", L"Error", MB_ICONERROR);
        return false;
    }

    std::wstring temp_folder = temp_path;
    temp_folder += L"\\";
    temp_folder += uuid;

    if (!CreateDirectoryW(temp_folder.c_str(), nullptr))
    {
        MessageBoxW(nullptr, L"Failed to create temporary folder...", L"Error", MB_ICONERROR);
        return false;
    }

    *created_path = temp_folder;
    return true;
}

bool copy_directory(const std::wstring &source_directory, const std::wstring &destination_directory)
{
    if (!CreateDirectoryW(destination_directory.c_str(), nullptr))
    {
        return false;
    }

    WIN32_FIND_DATAW find_data;
    HANDLE h_find = FindFirstFileW((source_directory + L"\\*").c_str(), &find_data);

    if (h_find == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    do
    {
        const std::wstring file_name = find_data.cFileName;
        if (file_name != L"." && file_name != L"..")
        {
            const std::wstring source_file_path = source_directory + L"\\" + file_name;
            const std::wstring destination_file_path = destination_directory + L"\\" + file_name;

            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                copy_directory(source_file_path, destination_file_path);
            }
            else
            {
                if (!CopyFileW(source_file_path.c_str(), destination_file_path.c_str(), FALSE))
                {
                    FindClose(h_find);
                    return false;
                }
            }
        }
    } while (FindNextFileW(h_find, &find_data) != 0);

    FindClose(h_find);

    return true;
}

bool copy_development_files(std::wstring temp_folder_path)
{
    const wchar_t *source_path = L"C:\\Work\\xoaim\\client\\x64\\Release\\";

    const int arraySize = 5;
    std::wstring strings[arraySize] = {L"client.exe", L"Ultralight.dll", L"UltralightCore.dll", L"AppCore.dll", L"WebCore.dll"};

    for (int i = 0; i < arraySize; ++i)
    {
        const auto source_file = std::wstring(source_path + strings[i]);
        const auto destination_file = std::wstring(temp_folder_path + L"\\" + strings[i]);

        if (!CopyFileW(source_file.c_str(), destination_file.c_str(), FALSE))
        {
            MessageBoxW(nullptr, L"Failed to copy development files...", L"Error", MB_ICONERROR);
            return false;
        }
    }

    const auto assets = std::wstring(L"assets");
    const auto source_directory = std::wstring(source_path + assets);

    if (!copy_directory(source_directory, temp_folder_path + L"\\assets"))
    {
        MessageBoxW(nullptr, L"Failed to copy development files...", L"Error", MB_ICONERROR);
        return false;
    }

    return true;
}

bool fetch_production_files(std::wstring temp_folder_path)
{
    // ...

    return true;
}

bool delete_directory(const std::wstring &path)
{
    WIN32_FIND_DATAW find_data;
    HANDLE h_find = FindFirstFileW((path + L"\\*").c_str(), &find_data);

    if (h_find == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    do
    {
        const std::wstring file_name = find_data.cFileName;
        if (file_name != L"." && file_name != L"..")
        {
            const std::wstring file_path = path + L"\\" + file_name;

            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                delete_directory(file_path);
            }
            else
            {
                if (!DeleteFileW(file_path.c_str()))
                {
                    FindClose(h_find);
                    return false;
                }
            }
        }
    } while (FindNextFileW(h_find, &find_data) != 0);

    FindClose(h_find);

    return RemoveDirectoryW(path.c_str()) != 0;
}

bool launch_client(std::wstring temp_folder_path)
{
    std::wstring executable_path = temp_folder_path + L"\\client.exe";
    std::wstring cmd_args = L"";

    STARTUPINFOW startup_info;
    PROCESS_INFORMATION process_info;

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    if (!CreateProcessW(
            executable_path.c_str(),
            (LPWSTR)cmd_args.c_str(),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &startup_info,
            &process_info))
    {
        MessageBoxW(nullptr, L"Failed to launch client...", L"Error", MB_ICONERROR);
        return false;
    }

    WaitForSingleObject(process_info.hProcess, INFINITE);
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);

    return true;
}

int main()
{
    FreeConsole();

    std::wstring temp_folder_path;
    if (!create_temp_folder(&temp_folder_path))
    {
        goto exit;
    }

#ifdef DEBUG_BUILD
    if (!copy_development_files(temp_folder_path))
    {
        goto cleanup;
    }
#else
    if (!fetch_production_files(temp_folder_path))
    {
        goto cleanup;
    }
#endif

    // check steam running
    // ...

    if (!launch_client(temp_folder_path))
    {
        goto cleanup;
    }

cleanup:
    if (!delete_directory(temp_folder_path.c_str()))
    {
        MessageBoxW(nullptr, L"Failed to delete temporary files...", L"Error", MB_ICONERROR);
    }

    // delete file execution history
    // ...

exit:
    return 0;
}