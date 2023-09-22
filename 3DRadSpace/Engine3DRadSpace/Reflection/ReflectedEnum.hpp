#pragma once
#include "ReflectedObject.hpp"
#include "..\Algorithms\FixedArray.hpp"

enum class MyTestEnum
{
	None,
	Apple,
	Pineapple,
	Strawberry
};

namespace Engine3DRadSpace::Reflection
{
	struct EnumEntry
	{
		EnumEntry() = default;

		const std::string Name;
		int Value;
	};

	class IReflectedEnum
	{
		public:
			virtual const std::string Name() = 0;
			virtual const unsigned NumberOfEntries() = 0;
			virtual const EnumEntry operator[](unsigned entryId) = 0;

			struct Iterator
			{
				using iterator_category = std::contiguous_iterator_tag;
				using difference_type = std::ptrdiff_t;
				using value_type = EnumEntry;
				using pointer = EnumEntry*;
				using reference = EnumEntry&;
			private:
				pointer _ptr;
			};

			virtual ~IReflectedEnum() = default;
	};

	template<typename E> requires std::is_enum_v<E>
	class ReflectedEnum
	{
		std::string _name;
		unsigned _numEntries;
		Algorithms::FixedArray<EnumEntry> _entries;
	public:
		ReflectedEnum(const std::string& name, std::initializer_list<EnumEntry> entries) :
			_numEntries(entries.size()),
			_name(name)
			_entries(entries.size())
		{
		}
	};
}