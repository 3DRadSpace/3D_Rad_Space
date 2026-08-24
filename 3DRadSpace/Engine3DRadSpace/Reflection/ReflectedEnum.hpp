#pragma once
#include "ReflectedObject.hpp"
#include "../Core/Tag.hpp"
#include "EnumEntry.hpp"

namespace Engine3DRadSpace::Reflection
{
	/// <summary>
	/// Enumeration metadata type.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT ReflectedEnum
	{
		std::string _enumName;
		std::vector<EnumEntry> _entries;
		size_t _typeHash;
	public:
		/// <summary>
		/// Constructs an ReflectedEnum based of the given type and arguments.
		/// </summary>
		/// <typeparam name="E">Enum type.</typeparam>
		/// <param name="dummy">Use {} as an argument.</param>
		/// <param name="name">Visible name of this enum</param>
		/// <param name="entries">Enumeration entries, specified as (Name, int64_t value)</param>
		template<typename E> requires std::is_enum_v<E>
		ReflectedEnum(Tag<E> dummy, const std::string& name, std::initializer_list<EnumEntry> entries) :
			_enumName(name),
			_entries(entries),
			_typeHash(typeid(E).hash_code())
		{
		}
		/// <summary>
		/// Visible name of this enum.
		/// </summary>
		/// <returns>visible name</returns>
		const std::string EnumName() const noexcept;
		/// <summary>
		/// Returns the number of entries.
		/// </summary>
		/// <returns>number of entries.</returns>
		const size_t NumberOfEntries() const noexcept;
		/// <summary>
		/// Returns the entryID-th entry of this enum.
		/// </summary>
		/// <param name="entryId">Entry ID</param>
		const EnumEntry operator[](unsigned entryId) const noexcept;
		/// <summary>
		///	Returns the type hash code of this enum.
		/// </summary>
		/// <returns>typeid(E).hash_code()</returns>
		const size_t TypeHashCode() const noexcept;

		/// <summary>
		/// Begin iterator for entries.
		/// </summary>
		/// <returns>std::vector<EnumEntry>::iterator::begin()</returns>
		std::vector<EnumEntry>::iterator begin();
		/// <summary>
		/// End iterator for entries.
		/// </summary>
		/// <returns>std::vector<EnumEntry>::iterator::end()</returns>
		std::vector<EnumEntry>::iterator end();
	};
}