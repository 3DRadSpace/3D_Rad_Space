#pragma once
#include "../IDynamicCollider.hpp"
#include "../Math/Quaternion.hpp"
#include <PxRigidDynamic.h>
#include <PxPhysics.h>
#include "PxUptr.hpp"

namespace Engine3DRadSpace::Physics::NVPhysX
{
	class Joint;
	class E3DRSP_PHYSICS_OBJ_EXPORT DynamicCollider : public IDynamicCollider
	{
	protected:
		void _generateRigidbody();

		float GetMass() const override;
		void SetMass(float mass) override;

		float GetLinearDamping() const override;
		void SetLinearDamping(float linearDamping) override;

		float GetAngularDamping() const override;
		void SetAngularDamping(float angularDamping) override;

		float GetStaticFriction() const override;
		void SetStaticFriction(float friction) override;

		float GetDynamicFriction() const override;
		void SetDynamicFriction(float friction) override;

		float GetRestitution() const override;
		void SetRestitution(float restitution) override;

		Math::Vector3 GetLinearVelocity() const override;
		void SetLinearVelocity(const Math::Vector3 & linearVelocity) override;

		Math::Vector3 GetAngularVelocity() const override;
		void SetAngularVelocity(const Math::Vector3 & angularVelocity) override;

		Math::Vector3 GetMaxAngularVelocity() const override;
		void SetMaxAngularVelocity(const Math::Vector3 & maxAngularVelocity) override;

		Math::Vector3 GetPosition() const override;
		void SetPosition(const Math::Vector3& position) override;

		Math::Quaternion GetRotation() const override;
		void SetRotation(const Math::Quaternion& rotation) override;

		PxUPtr<physx::PxRigidDynamic> _rigidbody;
		PxUPtr<physx::PxMaterial> _material;	
	public:
		DynamicCollider(IPhysicsEngine* physics);

		DynamicCollider(DynamicCollider&&) noexcept = default;
		DynamicCollider& operator=(DynamicCollider&&) noexcept = default;

		void ApplyForce(const Math::Vector3& force) override;
		void ApplyForce(const Math::Vector3& force, const Math::Vector3& center) override;
		void ApplyTorque(const Math::Vector3& force) override;

		void ApplyAcceleration(const Math::Vector3& acc) override;
		void ApplyAngularAcceleration(const Math::Vector3& acc) override;

		std::optional<float> Intersects(const Math::Ray& r) override;
		void UpdateTransform() override;
		void UpdateTransform(const Math::Vector3& position, const Math::Quaternion& rotation) override;

		void AttachShape(const Math::BoundingBox& box) override;
		void AttachShape(const Math::BoundingSphere& sphere) override;

		void UpdateMassAndInertia() override;

		void SetKinematic(bool isKinematic) override;
		void AddLinearVelocity(const Math::Vector3& v) override;
		void AddAngularVelocity(const Math::Vector3& v) override;

		friend class PhysicsEngine;
		friend class Joint;

		~DynamicCollider() override = default;
	};
}