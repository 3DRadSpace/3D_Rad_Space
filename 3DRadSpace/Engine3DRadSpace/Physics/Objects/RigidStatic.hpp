#pragma once
#include "IPhysicsObject.hpp"
#include "../IStaticCollider.hpp"
#include "../../Objects/Impl/Skinmesh.hpp"

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents an static rigidboby made from an mesh collider.
	/// </summary>
	class E3DRSP_PHYSICS_OBJ_EXPORT RigidStatic : public IPhysicsObject
	{
		std::unique_ptr<IStaticCollider> _collider = nullptr;
		std::unique_ptr<std::string> _path;

		Graphics::Model3D* _model = nullptr;
		bool _reqTransformUpdate = false;

		struct physicsProperties
		{
			float linearDamping = 0.0f;
			float staticFriction = 0.0f;
			float dynamicFriction = 0.0f;
			float restitution = 0.0f;
		};

		std::unique_ptr<physicsProperties> _properties = std::make_unique<physicsProperties>();
	public:
		RigidStatic();
		RigidStatic(
			const std::string& name,
			bool enabled,
			bool visible,
			const std::filesystem::path& path,
			const Math::Vector3 position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One()
		);

		RigidStatic(RigidStatic&&) noexcept = default;
		RigidStatic& operator=(RigidStatic&&) noexcept = default;

		Engine3DRadSpace::Objects::RefModel3D Model;

		float GetLinearDamping() const noexcept;
		void SetLinearDamping(float linearDamping);

		float GetStaticFriction() const noexcept;
		void SetStaticFriction(float friction);

		float GetDynamicFriction() const noexcept;
		void SetDynamicFriction(float friction);

		float GetRestitution() const noexcept;
		void SetRestitution(float restitution);

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;
		void Draw3D() override;

		float Intersects(const Math::Ray& r) override;
		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		Reflection::UUID GetUUID() const noexcept override;

		IStaticCollider* GetCollider() const noexcept;
		Graphics::Model3D* GetModel() const noexcept;
		void RequestTransformUpdate();
		
		~RigidStatic() override = default;
	};
}

REFL_FWD(RigidStatic)