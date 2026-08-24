#pragma once
#include "IObject.hpp"
#include "../Core/IDrawable2D.hpp"
#include "../Math/Vector2.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Polymorphic interface for 2D objects.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT IObject2D : public IObject, public IDrawable2D
	{
	protected:
		explicit IObject2D(
			const std::string& name = "",
			bool enabled = false,
			bool visible = false,
			const Math::Vector2& pos = Math::Vector2::Zero(),
			const Math::Vector2& scale = Math::Vector2(0.1f, 0.1f),
			float rotation = 0.0f,
			const Math::Vector2& pivot = Math::Vector2::Zero(),
			float depth = 0.0f
		);
	public:
		/// <summary>
		/// Position of this object in screen coordinates.
		/// </summary>
		Math::Vector2 Position;
		/// <summary>
		/// Rotation pivot.
		/// </summary>
		Math::Vector2 RotationCenter;
		/// <summary>
		/// Scale of this object. Usually (1.0f, 1.0f).
		/// </summary>
		Math::Vector2 Scale;
		/// <summary>
		/// Z depth of this object. Used for layering 2D objects. Higher values are drawn on top of lower values.
		/// </summary>
		float Depth;
		/// <summary>
		/// Rotation of this object in radians.
		/// </summary>
		float Rotation;

		virtual ~IObject2D() = default;
	};
}