#pragma once
#include "PhysicsEngine.hpp"
#include "../ICharacterController.hpp"
#include <characterkinematic/PxCapsuleController.h>

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class E3DRSP_PHYSICS_OBJ_EXPORT CharacterController : public ICharacterController
	{
	protected:
		PxUPtr<physx::PxMaterial> _material;
		PxUPtr<physx::PxCapsuleController> _controller;
		Math::Vector3 _verticalVelocity = Math::Vector3::Zero();

		Math::Vector3 _position;
	public:
		CharacterController(IPhysicsEngine* physics, float height, float radius, const Math::Vector3& position = Math::Vector3::Zero());
		
		CharacterController(CharacterController&&) noexcept = default;
		CharacterController& operator=(CharacterController&&) noexcept = default;

		float GetMass() const override;
		void SetMass(float mass) override;

		void SetHeight(float height) override;
		float GetHeight() const override;

		void SetRadius(float radius) override;
		float GetRadius() const override;

		void SetMaxSlopeAngle(float angle) override;
		float GetMaxSlopeAngle() const override;

		Math::Vector3 GetGravity() const override;
		void SetGravity(const Math::Vector3& gravity) override;

		Math::Vector3 GetPosition() const override;
		void SetPosition(const Math::Vector3& position) override;

		Math::Quaternion GetRotation() const override;
		void SetRotation(const Math::Quaternion& rotation) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;
		void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) override;
		
		void Move(const Math::Vector3& displacement) override;
		void Jump(float height) override;
		bool IsGrounded() override;

		~CharacterController() override = default;

		friend class PhysicsEngine;
	};
}