#ifndef OBJECT_ATTRIBUTES_H
#define OBJECT_ATTRIBUTES_H

namespace nt
{

	struct OBJECT_ATTRIBUTES
	{
		unsigned long Length;
		void *RootDirectory;
		UNICODE_STRING *ObjectName;
		unsigned long Attributes;
		void *SecurityDescriptor;
		void *SecurityQualityOfService;
	};

}

#ifndef InitializeObjectAttributes
#define InitializeObjectAttributes(p, n, a, r, s)    \
	{                                                \
		(p)->Length = sizeof(nt::OBJECT_ATTRIBUTES); \
		(p)->RootDirectory = r;                      \
		(p)->Attributes = a;                         \
		(p)->ObjectName = n;                         \
		(p)->SecurityDescriptor = s;                 \
		(p)->SecurityQualityOfService = 0;           \
	}

#define OBJ_INHERIT 0x00000002L
#define OBJ_PERMANENT 0x00000010L
#define OBJ_EXCLUSIVE 0x00000020L
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_OPENIF 0x00000080L
#define OBJ_OPENLINK 0x00000100L
#define OBJ_KERNEL_HANDLE 0x00000200L
#define OBJ_FORCE_ACCESS_CHECK 0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP 0x00000800L
#define OBJ_DONT_REPARSE 0x00001000L
#define OBJ_VALID_ATTRIBUTES 0x00001FF2L
#endif

#endif