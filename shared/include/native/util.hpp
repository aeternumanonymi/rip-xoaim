#ifndef UTIL_H
#define UTIL_H

#include <intrin.h>

namespace nt
{
	__forceinline bool success(const NTSTATUS status)
	{
		return status >= 0;
	}

	__forceinline void *current_process()
	{
		return (void *)(-1);
	}

	__forceinline uint32_t process_id()
	{
#ifdef _WIN64
		const auto teb = __readgsqword(0x30);
		return *reinterpret_cast<uint32_t *>(teb + 0x40);
#else
		const auto teb = __readfsdword(0x18);
		return *reinterpret_cast<uint32_t *>(teb + 0x20);
#endif
	}
}

#endif
