#ifndef API_SET_H
#define API_SET_H

namespace nt
{

	struct API_SET_NAMESPACE
	{
		unsigned long Version;
		unsigned long Size;
		unsigned long Flags;
		unsigned long Count;
		unsigned long EntryOffset;
		unsigned long HashOffset;
		unsigned long HashFactor;
	};

	struct API_SET_HASH_ENTRY
	{
		unsigned long Hash;
		unsigned long Index;
	};

	struct API_SET_NAMESPACE_ENTRY
	{
		unsigned long Flags;
		unsigned long NameOffset;
		unsigned long NameLength;
		unsigned long HashedLength;
		unsigned long ValueOffset;
		unsigned long ValueCount;
	};

	struct API_SET_VALUE_ENTRY
	{
		unsigned long Flags;
		unsigned long NameOffset;
		unsigned long NameLength;
		unsigned long ValueOffset;
		unsigned long ValueLength;
	};

} // namespace nt

#endif
