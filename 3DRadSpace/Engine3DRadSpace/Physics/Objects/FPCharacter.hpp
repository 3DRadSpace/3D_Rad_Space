#pragma once
#include "IPhysicsObject.hpp"
#include "../../Objects/Impl/FreeCam.hpp"
#include "../ICharacterController.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	class E3DRSP_PHYSICS_OBJ_EXPORT FPCharacter : public Engine3DRadSpace::Objects::FreeCam
	{
	protected:
		IPhysicsEngine* _physics;
		std::unique_ptr<ICharacterController> _controller;
	public:
		FPCharacter(
			const std::string& name = "FPCharacter",
			bool visible = true,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& up = Math::Vector3::UnitY(),
			float aspectRatio = 4.0f / 3.0f,
			float fov = Math::ToRadians(65.0f),
			float npd = 0.01f,
			float fpd = 500.0f
		);

		FPCharacter(FPCharacter&&) noexcept = default;
		FPCharacter& operator=(FPCharacter&&) noexcept = default;

		float Radius = 0.5f;
		float Height = 1.8f;

		Input::Key Jump = Input::Key::Space;
		float JumpPower = 1.0f;

		void Initialize() override;
		void Update() override;
		void Draw3D() override;

		void Teleport(const Math::Vector3& position);
		void Teleport(const Math::Vector3& position, const Math::Quaternion& rotation);
		ICharacterController* GetController() const noexcept;

		Reflection::UUID GetUUID() const noexcept override;
		Math::Matrix4x4 GetViewMatrix() const noexcept override;

		~FPCharacter() override = default;
	};
}

REFL_FWD(FPCharacter)