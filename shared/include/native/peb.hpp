#ifndef PEB_H
#define PEB_H

#include <intrin.h>

namespace nt
{

	struct PEB_LDR_DATA32
	{
		unsigned long Length;
		unsigned char Initialized;
		conditional32<void *> SsHandle;
		LIST_ENTRY32 InLoadOrderModuleList;
		LIST_ENTRY32 InMemoryOrderModuleList;
		LIST_ENTRY32 InInitializationOrderModuleList;
		conditional32<void *> EntryInProgress;
		unsigned char ShutdownInProgress;
		conditional32<void *> ShutdownThreadId;
	};

	struct PEB_LDR_DATA64
	{
		unsigned long Length;
		unsigned char Initialized;
		conditional64<void *> SsHandle;
		LIST_ENTRY64 InLoadOrderModuleList;
		LIST_ENTRY64 InMemoryOrderModuleList;
		LIST_ENTRY64 InInitializationOrderModuleList;
		conditional64<void *> EntryInProgress;
		unsigned char ShutdownInProgress;
		conditional64<void *> ShutdownThreadId;
	};

#ifdef _WIN64
	using PEB_LDR_DATA = PEB_LDR_DATA64;
#else
	using PEB_LDR_DATA = PEB_LDR_DATA32;
#endif

	struct CURDIR32
	{
		UNICODE_STRING32 DosPath;
		conditional32<void *> Handle;
	};

	struct CURDIR64
	{
		UNICODE_STRING64 DosPath;
		conditional64<void *> Handle;
	};

#ifdef _WIN64
	using CURDIR = CURDIR64;
#else
	using CURDIR = CURDIR32;
#endif

	struct RTL_DRIVE_LETTER_CURDIR32
	{
		unsigned short Flags;
		unsigned short Length;
		unsigned long TimeStamp;
		STRING32 DosPath;
	};

	struct RTL_DRIVE_LETTER_CURDIR64
	{
		unsigned short Flags;
		unsigned short Length;
		unsigned long TimeStamp;
		STRING64 DosPath;
	};

#ifdef _WIN64
	using RTL_DRIVE_LETTER_CURDIR = RTL_DRIVE_LETTER_CURDIR64;
#else
	using RTL_DRIVE_LETTER_CURDIR = RTL_DRIVE_LETTER_CURDIR32;
#endif

	struct RTL_USER_PROCESS_PARAMETERS32
	{
		unsigned long MaximumLength;
		unsigned long Length;
		unsigned long Flags;
		unsigned long DebugFlags;
		conditional32<void *> ConsoleHandle;
		unsigned long ConsoleFlags;
		conditional32<void *> StandardInput;
		conditional32<void *> StandardOutput;
		conditional32<void *> StandardError;
		CURDIR32 CurrentDirectory;
		UNICODE_STRING32 DllPath;
		UNICODE_STRING32 ImagePathName;
		UNICODE_STRING32 CommandLine;
		conditional32<void *> Environment;
		unsigned long StartingX;
		unsigned long StartingY;
		unsigned long CountX;
		unsigned long CountY;
		unsigned long CountCharsX;
		unsigned long CountCharsY;
		unsigned long FillAttribute;
		unsigned long WindowFlags;
		unsigned long ShowWindowFlags;
		UNICODE_STRING32 WindowTitle;
		UNICODE_STRING32 DesktopInfo;
		UNICODE_STRING32 ShellInfo;
		UNICODE_STRING32 RuntimeData;
		RTL_DRIVE_LETTER_CURDIR32 CurrentDirectores[32];
		unsigned long EnvironmentSize;
	};

	struct RTL_USER_PROCESS_PARAMETERS64
	{
		unsigned long MaximumLength;
		unsigned long Length;
		unsigned long Flags;
		unsigned long DebugFlags;
		conditional64<void *> ConsoleHandle;
		unsigned long ConsoleFlags;
		conditional64<void *> StandardInput;
		conditional64<void *> StandardOutput;
		conditional64<void *> StandardError;
		CURDIR64 CurrentDirectory;
		UNICODE_STRING64 DllPath;
		UNICODE_STRING64 ImagePathName;
		UNICODE_STRING64 CommandLine;
		conditional64<void *> Environment;
		unsigned long StartingX;
		unsigned long StartingY;
		unsigned long CountX;
		unsigned long CountY;
		unsigned long CountCharsX;
		unsigned long CountCharsY;
		unsigned long FillAttribute;
		unsigned long WindowFlags;
		unsigned long ShowWindowFlags;
		UNICODE_STRING64 WindowTitle;
		UNICODE_STRING64 DesktopInfo;
		UNICODE_STRING64 ShellInfo;
		UNICODE_STRING64 RuntimeData;
		RTL_DRIVE_LETTER_CURDIR64 CurrentDirectores[32];
		unsigned long EnvironmentSize;
	};

#ifdef _WIN64
	using RTL_USER_PROCESS_PARAMETERS = RTL_USER_PROCESS_PARAMETERS64;
#else
	using RTL_USER_PROCESS_PARAMETERS = RTL_USER_PROCESS_PARAMETERS32;
#endif

	struct PEB32
	{
		unsigned char InheritedAddressSpace;
		unsigned char ReadImageFileExecOptions;
		unsigned char BeingDebugged;

		union
		{
			unsigned char BitField;
			struct
			{
				unsigned char ImageUsesLargePages : 1;
				unsigned char IsProtectedProcess : 1;
				unsigned char IsImageDynamicallyRelocated : 1;
				unsigned char SkipPatchingUser32Forwarders : 1;
				unsigned char IsPackagedProcess : 1;
				unsigned char IsAppContainer : 1;
				unsigned char IsProtectedProcessLight : 1;
				unsigned char IsLongPathAwareProcess : 1;
			};
		};

		conditional32<void *> Mutant;
		conditional32<void *> ImageBaseAddress;
		conditional32<PEB_LDR_DATA32 *> Ldr;
		conditional32<RTL_USER_PROCESS_PARAMETERS32 *> ProcessParameters;
		conditional32<void *> SubSystemData;
		conditional32<void *> ProcessHeap;
		conditional32<void *> FastPebLock;
		conditional32<void *> AtlThunkSListPtr;
		conditional32<void *> IFEOKey;

		union
		{
			unsigned long CrossProcessFlags;
			struct
			{
				unsigned long ProcessInJob : 1;
				unsigned long ProcessInitializing : 1;
				unsigned long ProcessUsingVEH : 1;
				unsigned long ProcessUsingVCH : 1;
				unsigned long ProcessUsingFTH : 1;
				unsigned long ProcessPreviouslyThrottled : 1;
				unsigned long ProcessCurrentlyThrottled : 1;
				unsigned long ProcessImagesHotPatched : 1; // REDSTONE5
				unsigned long ReservedBits0 : 24;
			};
		};

		union
		{
			conditional32<void *> KernelCallbackTable;
			conditional32<void *> UserSharedInfoPtr;
		};

		unsigned long SystemReserved[1];
		unsigned long AtlThunkSListPtr32;
		conditional32<API_SET_NAMESPACE *> ApiSetMap;
	};

	struct PEB64
	{
		unsigned char InheritedAddressSpace;
		unsigned char ReadImageFileExecOptions;
		unsigned char BeingDebugged;

		union
		{
			unsigned char BitField;
			struct
			{
				unsigned char ImageUsesLargePages : 1;
				unsigned char IsProtectedProcess : 1;
				unsigned char IsImageDynamicallyRelocated : 1;
				unsigned char SkipPatchingUser32Forwarders : 1;
				unsigned char IsPackagedProcess : 1;
				unsigned char IsAppContainer : 1;
				unsigned char IsProtectedProcessLight : 1;
				unsigned char IsLongPathAwareProcess : 1;
			};
		};

		conditional64<void *> Mutant;
		conditional64<void *> ImageBaseAddress;
		conditional64<PEB_LDR_DATA64 *> Ldr;
		conditional64<RTL_USER_PROCESS_PARAMETERS64 *> ProcessParameters;
		conditional64<void *> SubSystemData;
		conditional64<void *> ProcessHeap;
		conditional64<void *> FastPebLock;
		conditional64<void *> AtlThunkSListPtr;
		conditional64<void *> IFEOKey;

		union
		{
			unsigned long CrossProcessFlags;
			struct
			{
				unsigned long ProcessInJob : 1;
				unsigned long ProcessInitializing : 1;
				unsigned long ProcessUsingVEH : 1;
				unsigned long ProcessUsingVCH : 1;
				unsigned long ProcessUsingFTH : 1;
				unsigned long ProcessPreviouslyThrottled : 1;
				unsigned long ProcessCurrentlyThrottled : 1;
				unsigned long ProcessImagesHotPatched : 1; // REDSTONE5
				unsigned long ReservedBits0 : 24;
			};
		};

		union
		{
			conditional64<void *> KernelCallbackTable;
			conditional64<void *> UserSharedInfoPtr;
		};

		unsigned long SystemReserved[1];
		unsigned long AtlThunkSListPtr32;
		conditional64<API_SET_NAMESPACE *> ApiSetMap;
	};

#ifdef _WIN64
	using PEB = PEB64;
#else
	using PEB = PEB32;
#endif

	__forceinline PEB *peb() noexcept
	{
#ifdef _WIN64
		return reinterpret_cast<PEB *>(__readgsqword(0x60));
#else
		return reinterpret_cast<PEB *>(__readfsdword(0x30));
#endif
	}

}

#endif
