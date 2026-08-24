#pragma once
#include "ReflectedField.hpp"
#include "ReflectedEnum.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename E>
	concept ReflectableEnum = std::is_enum_v<E>;

	/// <summary>
	/// Reflected enumeration field interface.
	/// </summary>
	class E3DRSP_REFLECTION_EXPORT IReflectedEnumField: public IReflectedField
	{
	protected:
		IReflectedEnumField() = default;
		IReflectedEnumField(const IReflectedEnumField&) = default;
		IReflectedEnumField(IReflectedEnumField&&) = default;

		IReflectedEnumField& operator=(const IReflectedEnumField&) = default;
		IReflectedEnumField& operator=(IReflectedEnumField&&) = default;
	public:
		/// <summary>
		/// Gets the enum type reflection metadata.
		/// </summary>
		/// <returns></returns>
		virtual ReflectedEnum GetEnum() = 0;
		~IReflectedEnumField() = default;
	};
}