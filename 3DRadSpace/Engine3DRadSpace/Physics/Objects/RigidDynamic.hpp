#pragma once
#include "IPhysicsObject.hpp"
#include "../IDynamicCollider.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// A physics object with a dynamic rigidbody collider.
	/// </summary>
	class E3DRSP_PHYSICS_EXPORT RigidDynamic : public IPhysicsObject
	{
	protected:
		std::unique_ptr<IDynamicCollider> _collider;

		struct physicsProperties
		{
			float mass = 0.0f;
			float linearDamping = 0.0f;
			float angularDamping = 0.0f;
			float staticFriction = 0.0f;
			float dynamicFriction = 0.0f;
			float restitution = 0.0f;
			Math::Vector3 linearVelocity = Math::Vector3::Zero();
			Math::Vector3 angularVelocity = Math::Vector3::Zero();
			Math::Vector3 maxAngularVelocity = Math::Vector3(100.0f, 100.0f, 100.0f);
		};

		std::unique_ptr<physicsProperties> _properties = std::make_unique<physicsProperties>();

		bool _kinematic = false;
	public:
		RigidDynamic(
			const std::string& name = "RigidDynamic",
			bool enabled = true,
			bool visible = true,
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		RigidDynamic(RigidDynamic&&) noexcept = default;
		RigidDynamic& operator=(RigidDynamic&&) noexcept = default;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;

		float Intersects(const Math::Ray& r) override;
		Reflection::UUID GetUUID() const noexcept override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation = std::nullopt);

		float GetMass() const noexcept;
		void SetMass(float mass);

		float GetLinearDamping() const noexcept;
		void SetLinearDamping(float linearDamping);

		float GetAngularDamping() const noexcept;
		void SetAngularDamping(float angularDamping);

		float GetStaticFriction() const noexcept;
		void SetStaticFriction(float friction);

		float GetDynamicFriction() const noexcept;
		void SetDynamicFriction(float friction);

		float GetRestitution() const noexcept;
		void SetRestitution(float restitution);

		Math::Vector3 GetLinearVelocity() const noexcept;
		void SetLinearVelocity(const Math::Vector3& linearVelocity);

		Math::Vector3 GetAngularVelocity() const noexcept;
		void SetAngularVelocity(const Math::Vector3& angularVelocity);

		Math::Vector3 GetMaxAngularVelocity() const noexcept;
		void SetMaxAngularVelocity(const Math::Vector3& maxAngularVelocity);

		bool IsKinematic() const noexcept;
		void SetKinematic(bool isKinematic);

		IDynamicCollider* GetCollider() const noexcept;
	};
}

REFL_FWD(RigidDynamic)