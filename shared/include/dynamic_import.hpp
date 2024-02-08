#ifndef DYNAMIC_IMPORT_H
#define DYNAMIC_IMPORT_H

#include <fnv1a.hpp>
#include <native.hpp>
#include <mapped_image.hpp>
#include <algorithm>

#define find_import_inlined(import) \
	::memory::dynamic_import<fnv1a_constexpr(#import), decltype(&import)>::inlined()

#define find_import_cached(import) \
	::memory::dynamic_import<fnv1a_constexpr(#import), decltype(&import)>::cached()

namespace memory
{

	template <fnv1a::hash_type _Hash, typename _Ty>
	class dynamic_import
	{
	public:
		__declspec(noinline) static _Ty cached() noexcept
		{
			static _Ty result = {};
			if (!result)
			{
				result = reinterpret_cast<_Ty>(find_import());
			}
			return result;
		}

		static __forceinline _Ty inlined() noexcept
		{
			return reinterpret_cast<_Ty>(find_import());
		}

	private:
		static __forceinline void *find_import() noexcept
		{
			for (auto it = static_cast<nt::LIST_ENTRY *>(nt::peb()->Ldr->InLoadOrderModuleList.Flink);
				 it != &nt::peb()->Ldr->InLoadOrderModuleList;
				 it = static_cast<nt::LIST_ENTRY *>(it->Flink))
			{
				const auto pe = static_cast<const mapped_image *>(reinterpret_cast<nt::LDR_DATA_TABLE_ENTRY *>(it)->DllBase);
				const auto data_dir = pe->data_directory(nt::image_directory_entry_export);
				const auto exp_dir = reinterpret_cast<const nt::IMAGE_EXPORT_DIRECTORY *>(pe->as_uintptr() + data_dir->VirtualAddress);
				const auto names = reinterpret_cast<const std::uint32_t *>(pe->as_uintptr() + exp_dir->AddressOfNames);
				const auto funcs = reinterpret_cast<const std::uint32_t *>(pe->as_uintptr() + exp_dir->AddressOfFunctions);
				const auto ords = reinterpret_cast<const std::uint16_t *>(pe->as_uintptr() + exp_dir->AddressOfNameOrdinals);

				for (auto i = 0; i < (std::min)(exp_dir->NumberOfFunctions, exp_dir->NumberOfNames); ++i)
				{
					if (!names[i])
					{
						continue;
					}

					const auto name = pe->as<const char *>() + names[i];
					if (fnv1a_runtime(name) == _Hash)
					{
						return reinterpret_cast<void *>(pe->as_uintptr() + funcs[ords[i]]);
					}
				}
			}

			return nullptr;
		}
	};

}

#endif
