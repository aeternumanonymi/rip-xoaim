#ifndef STODI_H
#define STODI_H

namespace nt
{
	struct SYSTEM_TIMEOFDAY_INFORMATION
	{
		LARGE_INTEGER BootTime;
		LARGE_INTEGER CurrentTime;
		LARGE_INTEGER TimeZoneBias;
		unsigned long TimeZoneId;
		unsigned long Reserved;
		unsigned long long BootTimeBias;
		unsigned long long SleepTimeBias;
	};
}

#endif
