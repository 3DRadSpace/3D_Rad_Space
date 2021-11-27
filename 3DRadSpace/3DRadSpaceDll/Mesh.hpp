#pragma once
#include "MeshPart.hpp"

namespace Engine3DRadSpace
{
	/// <summary>
	/// Represents a 3D model's geometry
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class Mesh
	{
	public:
		/// <summary>
		/// Represents the sub meshes
		/// </summary>
		MeshPart<T>** MeshParts;
		/// <summary>
		/// Represents the number of sub meshes.
		/// </summary>
		size_t NumParts;
	};
}

