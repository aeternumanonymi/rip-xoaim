#ifndef PBI_H
#define PBI_H

namespace nt
{
	struct PROCESS_BASIC_INFORMATION
	{
		NTSTATUS ExitStatus;
		PEB *PebBaseAddress;
		unsigned long long AffinityMask;
		KPRIORITY BasePriority;
		void *UniqueProcessId;
		void *InheritedFromUniqueProcessId;
	};
}

#endif
