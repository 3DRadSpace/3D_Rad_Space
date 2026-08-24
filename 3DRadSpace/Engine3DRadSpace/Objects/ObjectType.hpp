#pragma once

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Object type enumeration used internally.
	/// </summary>
	enum class ObjectType : uint8_t
	{
		/// <summary>
		/// Unspecified or invalid.
		/// </summary>
		None = 0,
		/// <summary>
		/// Base type.
		/// </summary>
		IObject = 1,
		/// <summary>
		/// 2D object.
		/// </summary>
		IObject2D,
		/// <summary>
		/// 3D object.
		/// </summary>
		IObject3D,
	};
}