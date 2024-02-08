#ifndef SHI_H
#define SHI_H

namespace nt
{
	struct SYSTEM_HANDLE_TABLE_ENTRY
	{
		unsigned short unique_process_id{};
		unsigned short creator_backtrace_index{};
		unsigned char object_type_index{};
		unsigned char handle_attributes{};
		unsigned short handle_value{};
		void *object{};
		unsigned long granted_access{};
	};

	struct SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
	{
		void *object{};
		unsigned long unique_process_id{};
		unsigned long handle_value{};
		unsigned long granted_access{};
		unsigned short creator_backtrace_index{};
		unsigned short object_type_index{};
		unsigned long handle_attributes{};
		unsigned long reserved{};
	};

	struct SYSTEM_HANDLE_INFORMATION
	{
		unsigned long handle_count{};
		SYSTEM_HANDLE_TABLE_ENTRY handles[1];
	};

	struct SYSTEM_HANDLE_INFORMATION_EX
	{
		unsigned long handle_count{};
		unsigned long unk{};
		SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX handles[1];
	};
}

#endif