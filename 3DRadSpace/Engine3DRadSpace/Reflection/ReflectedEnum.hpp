#pragma once
#include "ReflectedObject.hpp"
#include "..\Algorithms\FixedArray.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace::Reflection
{
	struct EnumEntry
	{
		std::string VisibleName;
		int Value;
	};

	class DLLEXPORT ReflectedEnum
	{
		std::string _name;
		Algorithms::FixedArray<EnumEntry> _entries;
		size_t _typeHash;
	public:
		template<typename E> requires std::is_enum_v<E>
		ReflectedEnum(Tag<E> dummy, const std::string& name, std::initializer_list<EnumEntry> entries) :
			_name(name),
			_entries(entries),
			_typeHash(typeid(E).hash_code())
		{
		}

		const std::string Name() const;
		const size_t NumberOfEntries() const;
		const EnumEntry operator[](unsigned entryId) const;
		const size_t TypeHashCode() const;

		Algorithms::FixedArray<EnumEntry>::Iterator begin();
		Algorithms::FixedArray<EnumEntry>::Iterator end();
	};
}