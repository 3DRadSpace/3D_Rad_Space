#pragma once
#include "Camera.hpp"
#include "../../Input/Key.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// FreeCam is a camera that can be moved freely in the scene using a 6 DoF control scheme.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT FreeCam : public Camera
	{
	protected:
		Math::Vector2 _camCoords;
		Math::Vector3 _fwd;
		Math::Vector3 _dir;
	public:
		/// <summary>
		///	Complete FreeCam constructor.
		/// </summary>
		/// <param name="name">Name of this object</param>
		/// <param name="visible">Is the camera visible</param>
		/// <param name="pos">Initial position of the camera</param>
		/// <param name="rotation">Initial rotation of the camera</param>
		/// <param name="up">Up direction of the camera</param>
		/// <param name="aspectRatio">Aspect ratio of the camera</param>
		/// <param name="fov">Field of view of the camera</param>
		/// <param name="npd">Near plane distance of the camera</param>
		/// <param name="fpd">Far plane distance of the camera</param>
		explicit FreeCam(
			const std::string& name = "FreeCam",
			bool visible = true,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f,
			float fov = Math::ToRadians(65.0f),
			float npd = 0.01f,
			float fpd = 500.0f
		);
		/// <summary>
		/// Default move constructor for FreeCam.
		/// </summary>
		/// <param name="other">The other FreeCam to move from</param>
		FreeCam(FreeCam&& other) noexcept = default;
		/// <summary>
		/// Default move assignment operator for FreeCam.
		/// </summary>
		/// <param name="other">The other FreeCam to move from</param>
		/// <returns>The moved FreeCam</returns>
		FreeCam& operator=(FreeCam&& other) noexcept = default;
		/// <summary>
		/// Camera rotation sensitivity. The higher the value, the more sensitive the camera is to mouse movement.
		/// </summary>
		float Sensitivity = 0.01f;
		/// <summary>
		/// Camera movement speed in m/s.
		/// </summary>
		float MovementSpeed = 1.0f;
		/// <summary>
		/// Invert the X axis for mouse movement.
		/// </summary>
		bool InvertX = false;
		/// <summary>
		/// Invert the Y axis for mouse movement.
		/// </summary>
		bool InvertY = false;
		/// <summary>
		/// Enable elevation using the Elevate and Descent keys.
		/// </summary>
		bool EnableElevation = true;
		/// <summary>
		/// Is movement entirely disabled?
		/// </summary>
		bool Frozen = false;
		/// <summary>
		/// Forward key
		/// </summary>
		Input::Key Forward = Input::Key::W;
		/// <summary>
		/// Backward key
		/// </summary>
		Input::Key Backward = Input::Key::S;
		/// <summary>
		/// Left key
		/// </summary>
		Input::Key Left = Input::Key::A;
		/// <summary>
		/// Right key
		/// </summary>
		Input::Key Right = Input::Key::D;
		/// <summary>
		/// Elevate key
		/// </summary>
		Input::Key Elevate = Input::Key::Q;
		/// <summary>
		/// Descend key
		/// </summary>
		Input::Key Descend = Input::Key::E;
		/// <summary>
		/// Gets the camera's forward direction in world space.
		/// </summary>
		/// <returns>The direction the camera is heading</returns>
		Math::Vector3 ForwardDir() const noexcept;
		/// <summary>
		/// Sets the camera rotation using an input vector formed of radians.
		/// </summary>
		/// <param name="camCoords"></param>
		void SetCameraRotation(const Math::Vector2& camCoords) noexcept;
		/// <summary>
		///	Handles input for this object.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Gets the UUID of FreeCam class type.
		/// </summary>
		/// <returns>{FDA0C96A-3040-4E5C-B12C-D34577D99415}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the gizmo associated with this object.
		/// </summary>
		/// <returns></returns>
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}