#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
	class E3DRSP_PHYSICS_EXPORT ICharacterController : public ICollider
	{
	protected:
		ICharacterController(IPhysicsEngine *physics);

		ICharacterController(ICharacterController&&) noexcept = default;
		ICharacterController& operator=(ICharacterController&&) noexcept = default;

		ICharacterController(const ICharacterController&) = delete;
		ICharacterController& operator=(const ICharacterController&) = delete;

		float _height;
		float _radius;
		float _maxSlopeAngle = std::numbers::pi_v<float> / 4.0f;
		Math::Vector3 _gravity;
	public:
		virtual void Move(const Math::Vector3& displacement) = 0;
		virtual void Jump(float height) = 0;

		virtual float GetHeight() const = 0;
		virtual void SetHeight(float height) = 0;

		virtual float GetRadius() const = 0;
		virtual void SetRadius(float radius) = 0;

		virtual void SetMaxSlopeAngle(float angle) = 0;
		virtual float GetMaxSlopeAngle() const = 0;

		virtual void SetGravity(const Math::Vector3& gravity) = 0;
		virtual Math::Vector3 GetGravity() const = 0;

		virtual bool IsGrounded() = 0;

		~ICharacterController() override = default;
	};
}