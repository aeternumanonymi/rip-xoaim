#ifndef FNV1A_H
#define FNV1A_H

#include <type_traits>
#include <cstdint>

#define fnv1a_runtime(s) ::fnv1a::create_hash(s)
#define fnv1a_constexpr(s) ::std::integral_constant<::fnv1a::hash_type, ::fnv1a::create_hash(s)>::value

namespace fnv1a
{
	namespace detail
	{
		template <std::uint32_t Size = sizeof(void *)>
		struct hash_parameters;

		template <>
		struct hash_parameters<4>
		{
			using hash_type = std::uint32_t;
			static constexpr hash_type offset_basis = 0x811c9dc5;
			static constexpr hash_type prime = 0x01000193;
		};

		template <>
		struct hash_parameters<8>
		{
			using hash_type = std::uint64_t;
			static constexpr hash_type offset_basis = 0xcbf29ce484222325;
			static constexpr hash_type prime = 0x00000100000001b3;
		};
	}

	using parameters = detail::hash_parameters<>;
	using hash_type = parameters::hash_type;

	constexpr hash_type offset_basis = parameters::offset_basis;
	constexpr hash_type prime = parameters::prime;

	template <typename Ty, typename = std::enable_if<std::is_same_v<Ty, char> || std::is_same_v<Ty, wchar_t>>>
	[[nodiscard]] constexpr auto create_hash(const Ty *string) noexcept -> hash_type
	{
		hash_type hash = offset_basis;

		for (; *string; ++string)
		{
			hash ^= *string;
			hash *= prime;
		}

		return hash;
	}
}

#endif
