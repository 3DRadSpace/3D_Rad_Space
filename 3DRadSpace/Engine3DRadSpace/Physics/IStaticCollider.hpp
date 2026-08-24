#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
	/// <summary>
	/// Base polymorphic interface for static colliders.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT IStaticCollider : public ICollider
	{
protected:
	IStaticCollider(IPhysicsEngine* physics);

	IStaticCollider(const IStaticCollider&) = delete;
	IStaticCollider& operator=(const IStaticCollider&) = delete;

	IStaticCollider(IStaticCollider&&) noexcept = default;
	IStaticCollider& operator=(IStaticCollider&&) noexcept = default;

	float _linearDamping = 0.01f;
	float _staticFriction = 0.5f;
	float _dynamicFriction = 0.5f;
	float _restitution = 0.1f;
	public:
		/// <summary>
		/// Gets the linear damping of the static collider.
		/// </summary>
		/// <returns>The linear damping value.</returns>
		virtual float GetLinearDamping() const = 0;
		/// <summary>
		/// Sets the linear damping of the static collider.
		/// </summary>
		/// <param name="linearDamping">The linear damping value.</param>
		virtual void SetLinearDamping(float linearDamping) = 0;

		/// <summary>
		/// Gets the static friction of the static collider.
		/// </summary>
		/// <returns>The static friction value.</returns>
		virtual float GetStaticFriction() const = 0;
		/// <summary>
		/// Sets the static friction of the static collider.
		/// </summary>
		/// <param name="friction">The static friction value.</param>
		virtual void SetStaticFriction(float friction) = 0;
		/// <summary>
		///	Gets the dynamic friction of the static collider.
		/// </summary>
		/// <returns>The dynamic friction value.</returns>
		virtual float GetDynamicFriction() const = 0;
		/// <summary>
		/// Sets the dynamic friction of the static collider.
		/// </summary>
		/// <param name="friction">The dynamic friction value.</param>
		virtual void SetDynamicFriction(float friction) = 0;

		/// <summary>
		/// Gets the restitution of the static collider.
		/// </summary>
		/// <returns>The restitution value.</returns>
		virtual float GetRestitution() const = 0;
		/// <summary>
		/// Sets the restitution of the static collider.
		/// </summary>
		/// <param name="restitution">The restitution value.</param>
		virtual void SetRestitution(float restitution) = 0;
	};
}