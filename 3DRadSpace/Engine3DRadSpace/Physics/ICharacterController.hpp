#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Represents the interface for character controllers in physics engine implementations.
	/// </summary>
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
		/// <summary>
		///	Move the character with the specified displacement.
		/// </summary>
		/// <param name="displacement">The displacement vector to move the character by.</param>
		virtual void Move(const Math::Vector3& displacement) = 0;
		/// <summary>
		/// Try to jump the character with the specified height.
		/// </summary>
		/// <param name="height">The height to jump.</param>
		virtual void Jump(float height) = 0;
		/// <summary>
		/// Gets the height of the character controller capsule collider.
		/// </summary>
		/// <returns></returns>
		virtual float GetHeight() const = 0;
		/// <summary>
		/// Sets the height of the character controller capsule collider.
		/// </summary>
		/// <param name="height"></param>
		virtual void SetHeight(float height) = 0;
		/// <summary>
		/// Gets the radius of the character controller capsule collider.
		/// </summary>
		/// <returns>The radius of the character controller capsule collider.</returns>
		virtual float GetRadius() const = 0;
		/// <summary>
		/// Sets the radius of the character controller capsule collider.
		/// </summary>
		/// <param name="radius">The radius of the character controller capsule collider.</param>
		virtual void SetRadius(float radius) = 0;

		/// <summary>
		/// Sets the maximum slope angle the character can walk on.
		/// </summary>
		/// <param name="angle">The maximum slope angle in radians.</param>
		virtual void SetMaxSlopeAngle(float angle) = 0;
		/// <summary>
		/// Gets the maximum slope angle the character can walk on.
		/// </summary>
		/// <returns>The maximum slope angle in radians.</returns>
		virtual float GetMaxSlopeAngle() const = 0;

		/// <summary>
		/// Sets the gravity affecting the character.
		/// </summary>
		/// <param name="gravity">The gravity vector.</param>
		virtual void SetGravity(const Math::Vector3& gravity) = 0;
		/// <summary>
		/// Gets the gravity affecting the character.
		/// </summary>
		/// <returns>The gravity vector.</returns>
		virtual Math::Vector3 GetGravity() const = 0;

		/// <summary>
		/// Checks if the character is grounded.
		/// </summary>
		/// <returns>True if the character is grounded, false otherwise.</returns>
		virtual bool IsGrounded() = 0;

		~ICharacterController() override = default;
	};
}