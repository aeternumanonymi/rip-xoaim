#ifndef SPROCESSI_H
#define SPROCESSI_H

namespace nt
{
	struct SYSTEM_PROCESS_INFORMATION
	{
		unsigned long NextEntryOffset;
		unsigned long NumberOfThreads;
		LARGE_INTEGER WorkingSetPrivateSize;		// since VISTA
		unsigned long HardFaultCount;				// since WIN7
		unsigned long NumberOfThreadsHighWatermark; // since WIN7
		unsigned long long CycleTime;				// since WIN7
		LARGE_INTEGER CreateTime;
		LARGE_INTEGER UserTime;
		LARGE_INTEGER KernelTime;
		UNICODE_STRING ImageName;
		KPRIORITY BasePriority;
		void *UniqueProcessId;
		void *InheritedFromUniqueProcessId;
		unsigned long HandleCount;
		unsigned long SessionId;
		unsigned long long UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
		unsigned long long PeakVirtualSize;
		unsigned long long VirtualSize;
		unsigned long PageFaultCount;
		unsigned long long PeakWorkingSetSize;
		unsigned long long WorkingSetSize;
		unsigned long long QuotaPeakPagedPoolUsage;
		unsigned long long QuotaPagedPoolUsage;
		unsigned long long QuotaPeakNonPagedPoolUsage;
		unsigned long long QuotaNonPagedPoolUsage;
		unsigned long long PagefileUsage;
		unsigned long long PeakPagefileUsage;
		unsigned long long PrivatePageCount;
		LARGE_INTEGER ReadOperationCount;
		LARGE_INTEGER WriteOperationCount;
		LARGE_INTEGER OtherOperationCount;
		LARGE_INTEGER ReadTransferCount;
		LARGE_INTEGER WriteTransferCount;
		LARGE_INTEGER OtherTransferCount;
		SYSTEM_THREAD_INFORMATION Threads[1]; // SystemProcessInformation
											  // SYSTEM_EXTENDED_THREAD_INFORMATION Threads[1]; // SystemExtendedProcessinformation
											  // SYSTEM_EXTENDED_THREAD_INFORMATION + SYSTEM_PROCESS_INFORMATION_EXTENSION // SystemFullProcessInformation
	};
}

#endif
