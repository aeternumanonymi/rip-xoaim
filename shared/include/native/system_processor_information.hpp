#ifndef SPROCESSORI_H
#define SPROCESSORI_H

namespace nt
{
	struct SYSTEM_PROCESSOR_INFORMATION
	{
		unsigned short ProcessorArchitecture;
		unsigned short ProcessorLevel;
		unsigned short ProcessorRevision;
		unsigned short MaximumProcessors;
		unsigned long ProcessorFeatureBits;
	};
}

#endif
