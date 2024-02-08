#ifndef RTL_P_M_H
#define RTL_P_M_H

namespace nt
{
	struct RTL_PROCESS_MODULE_INFORMATION
	{
		void *Section;
		void *MappedBase;
		void *ImageBase;
		unsigned long ImageSize;
		unsigned long Flags;
		unsigned short LoadOrderIndex;
		unsigned short InitOrderIndex;
		unsigned short LoadCount;
		unsigned short OffsetToFileName;
		unsigned char FullPathName[256];
	};

	struct RTL_PROCESS_MODULES
	{
		unsigned long NumberOfModules;
		RTL_PROCESS_MODULE_INFORMATION Modules[1];
	};
}

#endif
