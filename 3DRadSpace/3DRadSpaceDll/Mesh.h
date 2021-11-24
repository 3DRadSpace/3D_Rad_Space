#pragma once
#include "MeshPart.h"

namespace Engine3DRadSpace
{
	template<class T>
	class Mesh
	{
	public:
		MeshPart<T>** MeshParts;
		size_t NumParts;
	};
}

