#ifndef NTAPI_H
#define NTAPI_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

__declspec(dllimport) nt::NTSTATUS(__stdcall NtReadVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG BufferSize,
	PULONG NumberOfBytesRead);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtWriteVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG BufferSize,
	PULONG NumberOfBytesRead);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtOpenProcess)(
	PHANDLE ProcessHandle,
	nt::ACCESS_MASK DesiredAccess,
	nt::OBJECT_ATTRIBUTES *ObjectAttributes,
	nt::CLIENT_ID *ClientId);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtOpenThread)(
	PHANDLE ThreadHandle,
	nt::ACCESS_MASK DesiredAccess,
	nt::OBJECT_ATTRIBUTES *ObjectAttributes,
	nt::CLIENT_ID *ClientId);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtSuspendThread)(
	HANDLE ThreadHandle,
	PULONG PreviousSuspendCount);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtResumeThread)(
	HANDLE ThreadHandle,
	PULONG SuspendCount);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtAlertResumeThread)(
	HANDLE ThreadHandle,
	PULONG SuspendCount);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtGetContextThread)(
	HANDLE ThreadHandle,
	PCONTEXT Context);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtSetContextThread)(
	HANDLE ThreadHandle,
	PCONTEXT Context);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtQuerySystemInformation)(
	nt::SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtQueryInformationProcess)(
	HANDLE ProcessHandle,
	nt::PROCESSINFOCLASS ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtProtectVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID *BaseAddress,
	PSIZE_T RegionSize,
	ULONG NewProtect,
	PULONG OldProtect);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtAllocateVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID *BaseAddress,
	ULONG_PTR ZeroBits,
	PSIZE_T RegionSize,
	ULONG AllocationType,
	ULONG Protect);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtFreeVirtualMemory)(
	HANDLE ProcessHandle,
	PVOID *BaseAddress,
	PSIZE_T RegionSize,
	ULONG FreeType);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtClose)(
	HANDLE Handle);

__declspec(dllimport) nt::NTSTATUS(__stdcall RtlAdjustPrivilege)(
	ULONG Privilege,
	BOOLEAN Enable,
	BOOLEAN CurrentThread,
	PBOOLEAN Enabled);

__declspec(dllimport) nt::NTSTATUS(__stdcall RtlInitUnicodeString)(
	nt::UNICODE_STRING *DestinationString,
	const wchar_t *SourceString);

__declspec(dllimport) nt::NTSTATUS(__stdcall RtlWow64GetThreadContext)(
	HANDLE hThread,
	PWOW64_CONTEXT lpContext);

__declspec(dllimport) nt::NTSTATUS(__stdcall RtlWow64SetThreadContext)(
	HANDLE hThread,
	CONST WOW64_CONTEXT *lpContext);

__declspec(dllimport) nt::NTSTATUS(__stdcall RtlWow64SuspendThread)(
	HANDLE hThread);

__declspec(dllimport) nt::NTSTATUS(__stdcall NtOpenFile)(
	PHANDLE FileHandle,
	nt::ACCESS_MASK DesiredAccess,
	nt::OBJECT_ATTRIBUTES *ObjectAttributes,
	nt::IO_STATUS_BLOCK *IoStatusBlock,
	ULONG ShareAccess,
	ULONG OpenOptions);

__declspec(dllimport) nt::NTSTATUS(__stdcall ZwLoadDriver)(
	nt::UNICODE_STRING *DriverPath);

__declspec(dllimport) nt::NTSTATUS(__stdcall ZwUnloadDriver)(
	nt::UNICODE_STRING *DriverPath);

#endif
