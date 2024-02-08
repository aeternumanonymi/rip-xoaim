#ifndef LDR_DATA_TABLE_ENTRY_H
#define LDR_DATA_TABLE_ENTRY_H

namespace nt
{

	struct LDR_DATA_TABLE_ENTRY32
	{
		LIST_ENTRY32 InLoadOrderLinks;
		LIST_ENTRY32 InMemoryOrderLinks;

		union
		{
			LIST_ENTRY32 InInitializationOrderLinks;
			LIST_ENTRY32 InProgressLinks;
		};

		conditional32<void *> DllBase;
		conditional32<void *> EntryPoint;
		unsigned long SizeOfImage;
		UNICODE_STRING32 FullDllName;
		UNICODE_STRING32 BaseDllName;
	};

	struct LDR_DATA_TABLE_ENTRY64
	{
		LIST_ENTRY64 InLoadOrderLinks;
		LIST_ENTRY64 InMemoryOrderLinks;

		union
		{
			LIST_ENTRY64 InInitializationOrderLinks;
			LIST_ENTRY64 InProgressLinks;
		};

		conditional64<void *> DllBase;
		conditional64<void *> EntryPoint;
		unsigned long SizeOfImage;
		UNICODE_STRING64 FullDllName;
		UNICODE_STRING64 BaseDllName;
	};

#ifdef _WIN64
	using LDR_DATA_TABLE_ENTRY = LDR_DATA_TABLE_ENTRY64;
#else
	using LDR_DATA_TABLE_ENTRY = LDR_DATA_TABLE_ENTRY32;
#endif

}

#endif
