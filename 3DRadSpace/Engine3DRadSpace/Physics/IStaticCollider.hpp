#pragma once
#include "ICollider.hpp"

namespace Engine3DRadSpace::Physics
{
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
		virtual float GetLinearDamping() const = 0;
		virtual void SetLinearDamping(float linearDamping) = 0;

		virtual float GetStaticFriction() const = 0;
		virtual void SetStaticFriction(float friction) = 0;

		virtual float GetDynamicFriction() const = 0;
		virtual void SetDynamicFriction(float friction) = 0;

		virtual float GetRestitution() const = 0;
		virtual void SetRestitution(float restitution) = 0;
	};
}