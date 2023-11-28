#pragma once
#include "ReflectedObject.hpp"
#include "..\Algorithms\FixedArray.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace::Reflection
{
#pragma warning(push)
#pragma warning(disable:26495)
	struct EnumEntry
	{
		std::string VisibleName;
		int Value;
	};
#pragma warning(pop)

	class DLLEXPORT ReflectedEnum
	{
		Algorithms::FixedArray<EnumEntry> _entries;
		size_t _typeHash;
	public:
		template<typename E> requires std::is_enum_v<E>
		ReflectedEnum(Tag<E> dummy, std::initializer_list<EnumEntry> entries) :
			_entries(entries),
			_typeHash(typeid(E).hash_code())
		{
		}

		const size_t NumberOfEntries() const;
		const EnumEntry operator[](unsigned entryId) const;
		const size_t TypeHashCode() const;

		Algorithms::FixedArray<EnumEntry>::Iterator begin();
		Algorithms::FixedArray<EnumEntry>::Iterator end();
	};
}