#pragma once
#include "IObject.hpp"
#include "../Core/IDrawable3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/BoundingBox.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Polymorphic interface for 3D objects.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT IObject3D : public IObject, public IDrawable3D
	{
	protected:
		explicit IObject3D(const std::string& name = "", bool enabled = false, bool visible = false, const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Vector3& pivot = Math::Vector3::Zero(), const Math::Quaternion& rotation = Math::Quaternion(), const Math::Vector3& scale = Math::Vector3::One());

		IObject3D(const IObject3D&) noexcept = delete;
		IObject3D& operator=(const IObject3D&) noexcept = delete;

		IObject3D(IObject3D&&) noexcept = default;
		IObject3D& operator=(IObject3D&&) noexcept = default;
	public:
		/// <summary>
		/// Position in world space of this object.
		/// </summary>
		Math::Vector3 Position;
		/// <summary>
		/// Rotation pivot.
		/// </summary>
		Math::Vector3 RotationCenter;
		/// <summary>
		/// Rotation of this object. Default is (0,0,0,1) (identity quaternion).
		/// </summary>
		Math::Quaternion Rotation;
		/// <summary>
		/// Scale of this object. Default is (1,1,1).
		/// </summary>
		Math::Vector3 Scale;
		/// <summary>
		/// Gets the world matrix of this object, considering the entire hierarchy of parent objects.
		/// </summary>
		/// <returns>World matrix of this object</returns>
		virtual Math::Matrix4x4 GetModelMatrix() const;
		/// <summary>
		/// Gets the local transformation matrix of this object, considering only its own position, rotation, and scale.
		/// </summary>
		/// <returns>Local transformation matrix of this object</returns>
		virtual Math::Matrix4x4 GetLocalMatrix() const;
		/// <summary>
		/// Returns the distance from the ray origin to the intersection point, or NaN if there is no intersection.
		/// </summary>
		/// <param name="r">Ray in world space</param>
		/// <returns>Distance from the ray origin to the intersection point, or NaN if there is no intersection</returns>
		virtual float Intersects(const Math::Ray &r) const = 0;
		
		/// <summary>
		/// Gets the axis-aligned bounding box of this object in world space. Used for culling and intersections.
		/// </summary>
		/// <returns>Axis-aligned bounding box of this object</returns>
		virtual Math::BoundingBox GetBoundingBox() const noexcept;

		~IObject3D() = default;
	};
}
