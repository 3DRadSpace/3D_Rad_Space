#pragma once
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Base type for all objects that update the view/projection matrices.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT ICamera
	{
	protected:
		ICamera(
			const Math::Vector3& normal,
			float aspectRatio,
			float fov,
			float npd,
			float fpd
		);

		ICamera(const ICamera&) = delete;
		ICamera& operator=(const ICamera&) = delete;

		ICamera(ICamera&&) noexcept = default;
		ICamera& operator=(ICamera&&) noexcept = default;
	public:
		Math::Vector3 Normal;

		float AspectRatio;
		float FieldOfView;
		float NearPlaneDistance;
		float FarPlaneDistance;

		virtual Math::Matrix4x4 GetViewMatrix() const noexcept = 0;
		virtual Math::Matrix4x4 GetProjectionMatrix() const = 0;

		virtual ~ICamera() = default;
	};
}