#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Reflection
{
	struct UUID
	{
		unsigned long  Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[8];

		bool operator ==(const UUID &) const = default;
		bool operator !=(const UUID &) const = default;
	};
}

