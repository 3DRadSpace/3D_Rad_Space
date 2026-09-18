#pragma once
#include "RigidDynamic.hpp"

namespace Engine3DRadSpace::Objects
{
	class Skinmesh;
}

namespace Engine3DRadSpace::Physics::Objects
{
	/// <summary>
	/// Represents an projectile spawner. Spawned projectiles are IDynamicCollider instances that aren't separate objects.
	/// </summary>
	/// <remarks>
	/// Having RigidDynamic child will specify the collider shape of the projectile.
	/// Having a Skinmesh child will specify the visual mesh of the projectile.
	/// </remarks>
	class E3DRSP_PHYSICS_OBJ_EXPORT Projectile : public IPhysicsObject
	{
		struct ProjectileInfo
		{
			IDynamicCollider* instance;
			float lifetime;
		};

		std::vector<ProjectileInfo> _projectiles;

		RigidDynamic* _baseCollider = nullptr;
		Engine3DRadSpace::Objects::Skinmesh* _baseMesh = nullptr;

		ProjectileInfo _createProjectile();
	public:
		Projectile(
			const std::string& name = "Projectile",
			const Math::Vector3& position = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			float power = 10.0f,
			float lifetime = 5.0f,
			int maxProjectiles = 10
		);

		float Power;
		float Lifetime;
		int MaxProjectiles;
		
		/// <summary>
		/// Returns the idx-th projectile.
		/// </summary>
		/// <param name="idxProjectile">Projectile index. Range is [0, MaxProjectiles)</param>
		/// <returns></returns>
		IDynamicCollider* operator[](size_t idxProjectile) const;
		float GetLifetime(size_t idxProjectile) const;

		Math::Vector3 GetDirection() const noexcept;
		/// <inheritdoc/>
		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		Reflection::UUID GetUUID() const noexcept override;

		Engine3DRadSpace::Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		void Draw3D() override;

		float Intersects(const Math::Ray& r) const override;

	};
}

REFL_FWD(Projectile)