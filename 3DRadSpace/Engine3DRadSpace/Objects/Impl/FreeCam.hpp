#pragma once
#include "Camera.hpp"
#include "../../Input/Key.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT FreeCam : public Camera
	{
	protected:
		Math::Vector2 _camCoords;
		Math::Vector3 _fwd;
		Math::Vector3 _dir;
	public:
		FreeCam(
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

		FreeCam(FreeCam&&) noexcept = default;
		FreeCam& operator=(FreeCam&&) noexcept = default;

		float Sensitivity = 0.01f;
		float MovementSpeed = 1.0f;
		bool InvertX = false;
		bool InvertY = false;
		bool EnableElevation = true;
		bool Frozen = false;

		Input::Key Forward = Input::Key::W;
		Input::Key Backward = Input::Key::S;
		Input::Key Left = Input::Key::A;
		Input::Key Right = Input::Key::D;
		Input::Key Elevate = Input::Key::Q;
		Input::Key Descend = Input::Key::E;

		Math::Vector3 ForwardDir() const noexcept;
		void SetCameraRotation(const Math::Vector2& camCoords) noexcept;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}