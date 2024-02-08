#ifndef IO_STATUS_BLOCK_H
#define IO_STATUS_BLOCK_H

namespace nt
{

	struct IO_STATUS_BLOCK
	{
		union
		{
			NTSTATUS Status;
			void *Pointer;
		};

		std::uintptr_t Information;
	};

}

#endif
