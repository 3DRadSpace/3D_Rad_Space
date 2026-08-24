#pragma once
#include "IStaticCollider.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Base polymorphic type for dynamic physics objects that can move and interact with forces in the scene.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IDynamicCollider: public IStaticCollider
	{
	protected:
		float _angularDamping = 0;
		Math::Vector3 _linearVelocity = Math::Vector3::Zero();
		Math::Vector3 _angularVelocity = Math::Vector3::Zero();
		Math::Vector3 _maxAngularVelocity = Math::Vector3(100.0f, 100.0f, 100.0f);
		
		IDynamicCollider(IPhysicsEngine* physics);

		IDynamicCollider(const IDynamicCollider&) = delete;
		IDynamicCollider& operator=(const IDynamicCollider&) = delete;

		IDynamicCollider(IDynamicCollider&&) noexcept = default;
		IDynamicCollider& operator=(IDynamicCollider&&) noexcept = default;
	public:
		/// <summary>
		/// Gets the angular damping of the dynamic collider.
		/// </summary>
		/// <returns>The angular damping value.</returns>
		virtual float GetAngularDamping() const = 0;
		/// <summary>
		/// Sets the angular damping of the dynamic collider.
		/// </summary>
		/// <param name="angularDamping">The angular damping value.</param>
		virtual void SetAngularDamping(float angularDamping) = 0;
		/// <summary>
		/// Gets the velocity of the dynamic collider.
		/// </summary>
		/// <returns>linear velocity</returns>
		virtual Math::Vector3 GetLinearVelocity() const = 0;
		/// <summary>
		/// Sets the velocity of the dynamic collider.
		/// </summary>
		/// <param name="linearVelocity">The linear velocity vector.</param>
		virtual void SetLinearVelocity(const Math::Vector3& linearVelocity) = 0;
		/// <summary>
		/// Gets the angular velocity of the dynamic collider.
		/// </summary>
		/// <returns>The angular velocity vector.</returns>
		virtual Math::Vector3 GetAngularVelocity() const = 0;
		/// <summary>
		/// Sets the angular velocity of the dynamic collider.
		/// </summary>
		/// <param name="angularVelocity">The angular velocity vector.</param>
		virtual void SetAngularVelocity(const Math::Vector3& angularVelocity) = 0;
		
		/// <summary>
		/// Gets the maximum angular velocity of the dynamic collider.
		/// </summary>
		/// <returns>The maximum angular velocity vector.</returns>
		virtual Math::Vector3 GetMaxAngularVelocity() const = 0;
		/// <summary>
		/// Sets the maximum angular velocity of the dynamic collider.
		/// </summary>
		/// <returns>The maximum angular velocity vector.</returns>
		virtual void SetMaxAngularVelocity(const Math::Vector3& maxAngularVelocity) = 0;
		/// <summary>
		/// Attaches an box shape to this dynamic collider.
		/// </summary>
		/// <param name="box">boundingbox</param>
		virtual void AttachShape(const Math::BoundingBox& box) = 0;
		/// <summary>
		/// Attaches an sphere shape to this dynamic collider.
		/// </summary>
		/// <param name="sphere">boundingsphere</param>
		virtual void AttachShape(const Math::BoundingSphere& sphere) = 0;
		/// <summary>
		///	Updates the mass and inertia.
		/// </summary>
		virtual void UpdateMassAndInertia() = 0;
		/// <summary>
		/// Applies an linear force to this dynamic collider.
		/// </summary>
		/// <param name="force">force</param>
		virtual void ApplyForce(const Math::Vector3& force) = 0;
		/// <summary>
		/// Applies an force to this dynamic collider with a center that can cause angular motion.
		/// </summary>
		/// <param name="force">force</param>
		/// <param name="center">center</param>
		virtual void ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		/// <summary>
		/// Applies an torque to this dynamic collider.
		/// </summary>
		/// <param name="force">force</param>
		virtual void ApplyTorque(const Math::Vector3& force) = 0;
		/// <summary>
		/// Applies acceleration to this dynamic collider.
		/// </summary>
		/// <param name="acc">acceleration</param>
		virtual void ApplyAcceleration(const Math::Vector3& acc) = 0;
		/// <summary>
		/// Applies angular acceleration to this dynamic collider.
		/// </summary>
		/// <param name="acc">angular acceleration</param>
		virtual void ApplyAngularAcceleration(const Math::Vector3& acc) = 0;
		/// <summary>
		/// Sets whether this dynamic collider is kinematic or not.
		/// </summary>
		/// <remarks>
		/// Kinematic colliders are not affected by forces and can be moved manually, while non-kinematic colliders are affected by physics forces and collisions.
		/// </remarks>
		/// <param name="isKinematic">true to make the collider kinematic, false otherwise</param>
		virtual void SetKinematic(bool isKinematic) = 0;
		/// <summary>
		///	Adds linear velocity to this dynamic collider.
		/// </summary>
		/// <param name="v">linear velocity to add</param>
		virtual void AddLinearVelocity(const Math::Vector3& v) = 0;
		/// <summary>
		///	Adds angular velocity to this dynamic collider.
		/// </summary>
		/// <param name="v">angular velocity to add</param>
		virtual void AddAngularVelocity(const Math::Vector3& v) = 0;
	};
}