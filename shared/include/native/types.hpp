#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace nt
{
	using NTSTATUS = long;
	using ACCESS_MASK = unsigned long;
	using KPRIORITY = long;

	using GDI_HANDLE_BUFFER32 = unsigned long[34];
	using tls_callback_fn = void(__stdcall *)(void *, unsigned long, void *);
}

#endif
