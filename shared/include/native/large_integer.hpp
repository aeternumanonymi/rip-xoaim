#ifndef IO_STATUS_BLOCK_H
#define IO_STATUS_BLOCK_H

namespace nt
{

	using LARGE_INTEGER = union
	{
		struct
		{
			unsigned long LowPart;
			long HighPart;
		};

		struct
		{
			unsigned long LowPart;
			long HighPart;
		} u;

		long long QuadPart;
	};

	using ULARGE_INTEGER = union
	{
		struct
		{
			unsigned long LowPart;
			unsigned long HighPart;
		};

		struct
		{
			unsigned long LowPart;
			unsigned long HighPart;
		} u;

		unsigned long long QuadPart;
	};

}

#endif
