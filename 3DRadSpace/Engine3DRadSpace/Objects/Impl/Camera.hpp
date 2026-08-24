#pragma once
#include "../ICamera.hpp"
#include "../IObject3D.hpp"
#include "../../Math/Math.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D Camera.
	/// </summary>
	/// <remarks>
	/// This object updates the view, and projection matrices in the Draw3D() method. You may manually set these matrices without this.
	/// </remarks>
	class E3DRSP_OBJECTS_IMPL_EXPORT Camera : public IObject3D, public ICamera
	{
	public:
		/// <summary>
		/// Complete camera constructor.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Visibility of the camera</param>
		/// <param name="pos">Position of the camera</param>
		/// <param name="rotation">Rotation of the camera</param>
		/// <param name="up">Up direction of the camera</param>
		/// <param name="aspectRatio">Aspect ratio of the camera</param>
		/// <param name="fov">Field of view of the camera in radians</param>
		/// <param name="npd">Near plane distance of the camera</param>
		/// <param name="fpd">Far plane distance of the camera</param>
		Camera(
			const std::string& name = "Camera",
			bool visible = true,
			const Math::Vector3 &pos = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3 &up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f, 
			float fov = Math::ToRadians(65.0f), 
			float npd = 0.01f,
			float fpd = 500.0f
		);
		/// <summary>
		/// Move constructor for Camera.
		/// </summary>
		/// <param name="other">The Camera to move from</param>
		Camera(Camera&&) noexcept = default;
		/// <summary>
		/// Move assignment operator for Camera.
		/// </summary>
		/// <param name="other">The Camera to move from</param>
		Camera& operator=(Camera&&) noexcept = default;

		/// <summary>
		/// Updates the camera.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="path">unused</param>
		void Load(const std::filesystem::path &path) override;

		Math::Matrix4x4 GetModelMatrix() const override;
		/// <summary>
		/// Gets the View matrix of the camera.
		/// </summary>
		/// <returns>View matrix</returns>
		Math::Matrix4x4 GetViewMatrix() const noexcept override;
		Math::Matrix4x4 GetProjectionMatrix() const override;

		/// <summary>
		/// Sets the view and projection matrices.
		/// </summary>
		void Draw3D() override;

		/// <summary>
		/// Sets an internal reference in Game::Objects list.
		/// </summary>
		void Update() override;

		/// <summary>
		/// Same as both Draw3D() and Update() as if the camera is enabled.
		/// </summary>
		void ForceUpdate();

		void SetLookAt(const Math::Vector3& lookAt);

		float Intersects(const Math::Ray &r) const override;
		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		~Camera() override;
	};
}

REFL_FWD(Camera)