#ifndef MAPPED_IMAGE_HPP
#define MAPPED_IMAGE_HPP

#include <native.hpp>

template <bool Wow64>
class _Mapped_image
{
public:
	_Mapped_image() = delete;
	_Mapped_image(const _Mapped_image<Wow64> &) = delete;

	template <typename Ty>
	[[nodiscard]] __forceinline Ty as() noexcept
	{
		return reinterpret_cast<Ty>(this);
	}

	template <typename Ty>
	[[nodiscard]] __forceinline const Ty as() const noexcept
	{
		return reinterpret_cast<const Ty>(this);
	}

	[[nodiscard]] __forceinline std::uintptr_t as_uintptr() const noexcept
	{
		return this->as<std::uintptr_t>();
	}

	[[nodiscard]] __forceinline const nt::IMAGE_DOS_HEADER *dos_header() const noexcept
	{
		return this->as<const nt::IMAGE_DOS_HEADER *>();
	}

	[[nodiscard]] __forceinline const auto *nt_headers() const noexcept
	{
		using _Type = std::conditional_t<Wow64, nt::IMAGE_NT_HEADERS32, nt::IMAGE_NT_HEADERS64>;
		return reinterpret_cast<const _Type *>(this->as_uintptr() + this->dos_header()->e_lfanew);
	}

	[[nodiscard]] __forceinline const auto *optional_header() const noexcept
	{
		return &nt_headers()->OptionalHeader;
	}

	[[nodiscard]] __forceinline const nt::IMAGE_FILE_HEADER *file_header() const noexcept
	{
		return &nt_headers()->FileHeader;
	}

	[[nodiscard]] __forceinline std::uint32_t size_of_image() const noexcept
	{
		return optional_header()->SizeOfImage;
	}

	[[nodiscard]] __forceinline const nt::IMAGE_DATA_DIRECTORY *data_directory(const std::uint8_t dir) const noexcept
	{
		return &optional_header()->DataDirectory[dir];
	}

	[[nodiscard]] __forceinline bool is_wow64() const noexcept
	{
		return this->optional_header()->Magic == nt::image_nt_optional_hdr32_magic;
	}

	[[nodiscard]] __forceinline const nt::IMAGE_SECTION_HEADER *section_header() const noexcept
	{
		return reinterpret_cast<const nt::IMAGE_SECTION_HEADER *>(reinterpret_cast<std::uintptr_t>(this->optional_header()) + this->file_header()->SizeOfOptionalHeader);
	}
};

using mapped_image = _Mapped_image<sizeof(void *) == 4>;
using mapped_image32 = _Mapped_image<true>;
using mapped_image64 = _Mapped_image<false>;

#endif
