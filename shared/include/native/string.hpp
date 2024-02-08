#ifndef STRING_H
#define STRING_H

namespace nt
{
	struct STRING32
	{
		unsigned short Length;
		unsigned short MaximumLength;
		conditional32<char *> Buffer;
	};

	struct STRING64
	{
		unsigned short Length;
		unsigned short MaximumLength;
		conditional64<char *> Buffer;
	};

#ifdef _WIN64
	using STRING = STRING64;
#else
	using STRING = STRING32;
#endif
}

#endif