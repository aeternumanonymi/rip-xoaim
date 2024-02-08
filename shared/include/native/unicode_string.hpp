#ifndef UNICODE_STRING_H
#define UNICODE_STRING_H

namespace nt
{
	struct UNICODE_STRING32
	{
		unsigned short Length;
		unsigned short MaximumLength;
		conditional32<wchar_t *> Buffer;
	};

	struct UNICODE_STRING64
	{
		unsigned short Length;
		unsigned short MaximumLength;
		conditional64<wchar_t *> Buffer;
	};

#ifdef _WIN64
	using UNICODE_STRING = UNICODE_STRING64;
#else
	using UNICODE_STRING = UNICODE_STRING32;
#endif
}

#endif
