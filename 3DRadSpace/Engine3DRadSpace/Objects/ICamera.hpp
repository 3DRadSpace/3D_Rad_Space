#pragma once
#include "../Math/Math.hpp"
#include "../Reflection/Reflection.hpp"
#include "../Math/ViewingFrustum.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Base type for all objects that update the view/projection matrices.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT ICamera
	{
	protected:
		/// <summary>
		/// ICamera complete constructor
		/// </summary>
		/// <param name="normal">Normal vector of the camera.</param>
		/// <param name="aspectRatio">Aspect ratio of the camera.</param>
		/// <param name="fov">Field of view of the camera.</param>
		/// <param name="npd">Near plane distance of the camera.</param>
		/// <param name="fpd">Far plane distance of the camera.</param>
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
		/// <summary>
		/// Normal vector of the camera.
		/// </summary>
		Math::Vector3 Normal;
		/// <summary>
		///	Aspect ratio of the camera (width / height).
		/// </summary>
		float AspectRatio;
		/// <summary>
		/// Field of view in radians.
		/// </summary>
		float FieldOfView;
		/// <summary>
		/// Minimal rendering distance.
		/// </summary>
		float NearPlaneDistance;
		/// <summary>
		/// Maximum rendering distance.
		/// </summary>
		float FarPlaneDistance;
		/// <summary>
		/// Calculates the view matrix.
		/// </summary>
		/// <returns>The view matrix.</returns>
		virtual Math::Matrix4x4 GetViewMatrix() const noexcept = 0;
		/// <summary>
		/// Calculates the projection matrix.
		/// </summary>
		/// <returns>The projection matrix.</returns>
		virtual Math::Matrix4x4 GetProjectionMatrix() const = 0;

		/// <summary>
		/// Calculates the viewing frustum from the view and projection matrices.
		/// </summary>
		/// <returns>The viewing frustum.</returns>
		virtual Math::ViewingFrustum GetViewingFrustum() const;

		virtual ~ICamera() = default;
	};
}