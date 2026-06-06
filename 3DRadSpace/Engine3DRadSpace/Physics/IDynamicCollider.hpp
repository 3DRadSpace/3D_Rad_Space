#pragma once
#include "IStaticCollider.hpp"
#include "../Math/Quaternion.hpp"

namespace Engine3DRadSpace::Physics
{
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
		virtual float GetAngularDamping() const = 0;
		virtual void SetAngularDamping(float angularDamping) = 0;

		virtual Math::Vector3 GetLinearVelocity() const = 0;
		virtual void SetLinearVelocity(const Math::Vector3& linearVelocity) = 0;

		virtual Math::Vector3 GetAngularVelocity() const = 0;
		virtual void SetAngularVelocity(const Math::Vector3& angularVelocity) = 0;

		virtual Math::Vector3 GetMaxAngularVelocity() const = 0;
		virtual void SetMaxAngularVelocity(const Math::Vector3& linearVelocity) = 0;

		virtual void AttachShape(const Math::BoundingBox& box) = 0;
		virtual void AttachShape(const Math::BoundingSphere& sphere) = 0;

		virtual void ApplyForce(const Math::Vector3& force) = 0;
		virtual void ApplyForce(const Math::Vector3& force, const Math::Vector3& center) = 0;
		virtual void ApplyTorque(const Math::Vector3& force) = 0;

		virtual void ApplyAcceleration(const Math::Vector3& acc) = 0;
		virtual void ApplyAngularAcceleration(const Math::Vector3& acc) = 0;

		virtual void SetKinematic(bool isKinematic) = 0;

		virtual void AddLinearVelocity(const Math::Vector3& v) = 0;
		virtual void AddAngularVelocity(const Math::Vector3& v) = 0;
	};
}