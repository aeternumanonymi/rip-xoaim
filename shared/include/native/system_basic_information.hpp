#ifndef SBI_H
#define SBI_H

namespace nt
{
	struct SYSTEM_BASIC_INFORMATION
	{
		unsigned long Reserved;
		unsigned long TimerResolution;
		unsigned long PageSize;
		unsigned long NumberOfPhysicalPages;
		unsigned long LowestPhysicalPageNumber;
		unsigned long HighestPhysicalPageNumber;
		unsigned long AllocationGranularity;
		unsigned long long MinimumUserModeAddress;
		unsigned long long MaximumUserModeAddress;
		unsigned long long ActiveProcessorsAffinityMask;
		char NumberOfProcessors;
	};
}

#endif
