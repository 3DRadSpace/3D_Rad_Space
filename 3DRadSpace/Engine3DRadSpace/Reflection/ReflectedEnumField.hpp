#pragma once
#include "ReflectedField.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename A, typename B>
	struct same_size
	{
		enum { value = sizeof(A) == sizeof(B) };
	};

	template<typename A, typename B>
	constexpr bool same_size_v = same_size<A, B>::value;

	template<typename E>
	concept ReflectableEnum = std::is_enum_v<E> && same_size_v<E,int>;

	template<ReflectableEnum E>
	class ReflectedEnumField : public ReflectedField<int>
	{
	public:
		ReflectedEnumField(const size_t offset_obj_field, const std::string& visibleName, const std::string& description, E defaultValue) :
			ReflectedField(offset_obj_field, visibleName, description, defaultValue)
		{
		}


	};
}