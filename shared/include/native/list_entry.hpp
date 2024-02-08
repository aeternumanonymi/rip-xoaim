#ifndef LIST_ENTRY_H
#define LIST_ENTRY_H

namespace nt
{

	struct LIST_ENTRY32
	{
		conditional32<void *> Flink;
		conditional32<void *> Blink;
	};

	struct LIST_ENTRY64
	{
		conditional64<void *> Flink;
		conditional64<void *> Blink;
	};

#ifdef _WIN64
	using LIST_ENTRY = LIST_ENTRY64;
#else
	using LIST_ENTRY = LIST_ENTRY32;
#endif

}

#endif
