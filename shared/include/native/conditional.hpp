#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <type_traits>

namespace nt
{

	template <typename T>
	using conditional32 = std::conditional_t<sizeof(void *) * 8 == 32, T, unsigned long>;

	template <typename T>
	using conditional64 = std::conditional_t<sizeof(void *) * 8 == 64, T, unsigned long long>;

}

#endif
