#ifndef PE_H
#define PE_H

namespace nt
{

	constexpr auto image_directory_entry_export = 0;
	constexpr auto image_directory_entry_import = 1;
	constexpr auto image_directory_entry_basereloc = 5;
	constexpr auto image_sizeof_short_name = 8;
	constexpr auto image_directory_entry_tls = 9;
	constexpr auto image_directory_entry_delay_import = 13;
	constexpr auto image_num_of_directory_entries = 16;

	constexpr auto image_nt_optional_hdr32_magic = 0x10b;
	constexpr auto image_nt_optional_hdr64_magic = 0x20b;

	constexpr auto image_rel_based_absolute = 0;
	constexpr auto image_rel_based_highlow = 3;
	constexpr auto image_rel_based_dir64 = 10;

	constexpr auto image_ordinal_flag64 = 0x8000000000000000;
	constexpr auto image_ordinal_flag32 = 0x80000000;

	struct IMAGE_DOS_HEADER
	{
		unsigned short e_magic;	   // Magic number
		unsigned short e_cblp;	   // Bytes on last page of file
		unsigned short e_cp;	   // Pages in file
		unsigned short e_crlc;	   // Relocations
		unsigned short e_cparhdr;  // Size of header in paragraphs
		unsigned short e_minalloc; // Minimum extra paragraphs needed
		unsigned short e_maxalloc; // Maximum extra paragraphs needed
		unsigned short e_ss;	   // Initial (relative) SS value
		unsigned short e_sp;	   // Initial SP value
		unsigned short e_csum;	   // Checksum
		unsigned short e_ip;	   // Initial IP value
		unsigned short e_cs;	   // Initial (relative) CS value
		unsigned short e_lfarlc;   // File address of relocation table
		unsigned short e_ovno;	   // Overlay number
		unsigned short e_res[4];   // Reserved unsigned shorts
		unsigned short e_oemid;	   // OEM identifier (for e_oeminfo)
		unsigned short e_oeminfo;  // OEM information; e_oemid specific
		unsigned short e_res2[10]; // Reserved unsigned shorts
		long e_lfanew;			   // File address of new exe header
	};

	struct IMAGE_FILE_HEADER
	{
		unsigned short Machine;
		unsigned short NumberOfSections;
		unsigned long TimeDateStamp;
		unsigned long PointerToSymbolTable;
		unsigned long NumberOfSymbols;
		unsigned short SizeOfOptionalHeader;
		unsigned short Characteristics;
	};

	struct IMAGE_DATA_DIRECTORY
	{
		unsigned long VirtualAddress;
		unsigned long Size;
	};

	struct IMAGE_OPTIONAL_HEADER64
	{
		unsigned short Magic;
		unsigned char MajorLinkerVersion;
		unsigned char MinorLinkerVersion;
		unsigned long SizeOfCode;
		unsigned long SizeOfInitializedData;
		unsigned long SizeOfUninitializedData;
		unsigned long AddressOfEntryPoint;
		unsigned long BaseOfCode;
		unsigned long long ImageBase;
		unsigned long SectionAlignment;
		unsigned long FileAlignment;
		unsigned short MajorOperatingSystemVersion;
		unsigned short MinorOperatingSystemVersion;
		unsigned short MajorImageVersion;
		unsigned short MinorImageVersion;
		unsigned short MajorSubsystemVersion;
		unsigned short MinorSubsystemVersion;
		unsigned long Win32VersionValue;
		unsigned long SizeOfImage;
		unsigned long SizeOfHeaders;
		unsigned long CheckSum;
		unsigned short Subsystem;
		unsigned short DllCharacteristics;
		unsigned long long SizeOfStackReserve;
		unsigned long long SizeOfStackCommit;
		unsigned long long SizeOfHeapReserve;
		unsigned long long SizeOfHeapCommit;
		unsigned long LoaderFlags;
		unsigned long NumberOfRvaAndSizes;
		IMAGE_DATA_DIRECTORY DataDirectory[image_num_of_directory_entries];
	};

	struct IMAGE_OPTIONAL_HEADER32
	{
		unsigned short Magic;
		unsigned char MajorLinkerVersion;
		unsigned char MinorLinkerVersion;
		unsigned long SizeOfCode;
		unsigned long SizeOfInitializedData;
		unsigned long SizeOfUninitializedData;
		unsigned long AddressOfEntryPoint;
		unsigned long BaseOfCode;
		unsigned long BaseOfData;
		unsigned long ImageBase;
		unsigned long SectionAlignment;
		unsigned long FileAlignment;
		unsigned short MajorOperatingSystemVersion;
		unsigned short MinorOperatingSystemVersion;
		unsigned short MajorImageVersion;
		unsigned short MinorImageVersion;
		unsigned short MajorSubsystemVersion;
		unsigned short MinorSubsystemVersion;
		unsigned long Win32VersionValue;
		unsigned long SizeOfImage;
		unsigned long SizeOfHeaders;
		unsigned long CheckSum;
		unsigned short Subsystem;
		unsigned short DllCharacteristics;
		unsigned long SizeOfStackReserve;
		unsigned long SizeOfStackCommit;
		unsigned long SizeOfHeapReserve;
		unsigned long SizeOfHeapCommit;
		unsigned long LoaderFlags;
		unsigned long NumberOfRvaAndSizes;
		IMAGE_DATA_DIRECTORY DataDirectory[image_num_of_directory_entries];
	};

	struct IMAGE_NT_HEADERS64
	{
		unsigned long Signature;
		IMAGE_FILE_HEADER FileHeader;
		IMAGE_OPTIONAL_HEADER64 OptionalHeader;
	};

	struct IMAGE_NT_HEADERS32
	{
		unsigned long Signature;
		IMAGE_FILE_HEADER FileHeader;
		IMAGE_OPTIONAL_HEADER32 OptionalHeader;
	};

#ifdef _WIN64
	using IMAGE_NT_HEADERS = IMAGE_NT_HEADERS64;
#else
	using IMAGE_NT_HEADERS = IMAGE_NT_HEADERS32;
#endif

	struct IMAGE_EXPORT_DIRECTORY
	{
		unsigned long Characteristics;
		unsigned long TimeDateStamp;
		unsigned short MajorVersion;
		unsigned short MinorVersion;
		unsigned long Name;
		unsigned long Base;
		unsigned long NumberOfFunctions;
		unsigned long NumberOfNames;
		unsigned long AddressOfFunctions;	 // RVA from base of image
		unsigned long AddressOfNames;		 // RVA from base of image
		unsigned long AddressOfNameOrdinals; // RVA from base of image
	};

	struct IMAGE_BASE_RELOCATION
	{
		unsigned long VirtualAddress;
		unsigned long SizeOfBlock;
	};

	struct IMAGE_IMPORT_DESCRIPTOR
	{
		union
		{
			unsigned long Characteristics;	  // 0 for terminating null import descriptor
			unsigned long OriginalFirstThunk; // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
		};
		unsigned long TimeDateStamp; // 0 if not bound,
									 // -1 if bound, and real date\time stamp
									 //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
									 // O.W. date/time stamp of DLL bound to (Old BIND)

		unsigned long ForwarderChain; // -1 if no forwarders
		unsigned long Name;
		unsigned long FirstThunk; // RVA to IAT (if bound this IAT has actual addresses)
	};

	struct IMAGE_IMPORT_BY_NAME
	{
		unsigned short Hint;
		char Name[1];
	};

	struct IMAGE_DELAYLOAD_DESCRIPTOR
	{
		union
		{
			unsigned long AllAttributes;
			struct
			{
				unsigned long RvaBased : 1; // Delay load version 2
				unsigned long ReservedAttributes : 31;
			};
		} Attributes;

		unsigned long DllNameRVA;				  // RVA to the name of the target library (NULL-terminate ASCII string)
		unsigned long ModuleHandleRVA;			  // RVA to the HMODULE caching location (PHMODULE)
		unsigned long ImportAddressTableRVA;	  // RVA to the start of the IAT (PIMAGE_THUNK_DATA)
		unsigned long ImportNameTableRVA;		  // RVA to the start of the name table (PIMAGE_THUNK_DATA::AddressOfData)
		unsigned long BoundImportAddressTableRVA; // RVA to an optional bound IAT
		unsigned long UnloadInformationTableRVA;  // RVA to an optional unload info table
		unsigned long TimeDateStamp;			  // 0 if not bound,
												  // Otherwise, date/time of the target DLL
	};

	struct IMAGE_SECTION_HEADER
	{
		unsigned char Name[image_sizeof_short_name];

		union
		{
			unsigned long PhysicalAddress;
			unsigned long VirtualSize;
		} Misc;

		unsigned long VirtualAddress;
		unsigned long SizeOfRawData;
		unsigned long PointerToRawData;
		unsigned long PointerToRelocations;
		unsigned long PointerToLinenumbers;
		short NumberOfRelocations;
		short NumberOfLinenumbers;
		unsigned long Characteristics;
	};

	struct IMAGE_THUNK_DATA32
	{
		union
		{
			unsigned long ForwarderString; // PBYTE
			unsigned long Function;		   // PDWORD
			unsigned long Ordinal;
			unsigned long AddressOfData; // PIMAGE_IMPORT_BY_NAME
		} u1;
	};

	struct IMAGE_THUNK_DATA64
	{
		union
		{
			unsigned long long ForwarderString; // PBYTE
			unsigned long long Function;		// PDWORD
			unsigned long long Ordinal;
			unsigned long long AddressOfData; // PIMAGE_IMPORT_BY_NAME
		} u1;
	};

	struct IMAGE_TLS_DIRECTORY64
	{
		unsigned long long StartAddressOfRawData;
		unsigned long long EndAddressOfRawData;
		unsigned long long AddressOfIndex;
		unsigned long long AddressOfCallBacks;
		unsigned long SizeOfZeroFill;
		union
		{
			unsigned long Characteristics;
			struct
			{
				unsigned long Reserved0 : 20;
				unsigned long Alignment : 4;
				unsigned long Reserved1 : 8;
			};
		};
	};

	struct IMAGE_TLS_DIRECTORY32
	{
		unsigned long StartAddressOfRawData;
		unsigned long EndAddressOfRawData;
		unsigned long AddressOfIndex;
		unsigned long AddressOfCallBacks;
		unsigned long SizeOfZeroFill;
		union
		{
			unsigned long Characteristics;
			struct
			{
				unsigned long Reserved0 : 20;
				unsigned long Alignment : 4;
				unsigned long Reserved1 : 8;
			};
		};
	};

}

#endif
