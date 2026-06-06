#pragma once
#include "IObject.hpp"
#include "../Core/IDrawable3D.hpp"
#include "../Math/Ray.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Objects
{
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
		Math::Vector3 Position;

		Math::Vector3 RotationCenter;
		Math::Quaternion Rotation;

		Math::Vector3 Scale;

		virtual Math::Matrix4x4 GetModelMatrix();
		virtual Math::Matrix4x4 GetLocalMatrix();
		/// <summary>
		/// Returns the distance from the ray origin to the intersection point, or NaN if there is no intersection.
		/// </summary>
		/// <param name="r">Ray in world space</param>
		/// <returns>Distance from the ray origin to the intersection point, or NaN if there is no intersection</returns>
		virtual float Intersects(const Math::Ray &r) = 0;

		~IObject3D() = default;
	};
}
