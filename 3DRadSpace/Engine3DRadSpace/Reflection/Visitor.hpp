#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	template<typename ...Base>
	struct Visitor : Base...
	{
		using Base::operator()...;
	};
}