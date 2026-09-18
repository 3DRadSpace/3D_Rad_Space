#include "Projectile.hpp"
#include "../../Games/Game.hpp"
#include "../../Objects/Impl/Skinmesh.hpp"
#include "../../Objects/Impl/Box.hpp"
#include "../../Objects/Impl/Sphere.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics::Objects;

Projectile::Projectile(
	const std::string& name,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	float power,
	float lifetime,
	int maxProjectiles
) : IPhysicsObject(name, false, false, position, rotation, Vector3::One()),
	Power(power),
	Lifetime(lifetime),
	MaxProjectiles(maxProjectiles)
{
}


void Projectile::Initialize()
{
	auto setMeshChild = [this](IObject* obj) -> bool
	{
		if (auto mesh = dynamic_cast<Engine3DRadSpace::Objects::Skinmesh*>(obj); mesh != nullptr)
		{
			mesh->Visible = false;
			this->_baseMesh = mesh;
			return true;
		}
		return false;
	};

	for (auto child : Children)
	{
		if (auto dynCollider = dynamic_cast<RigidDynamic*>(child); dynCollider != nullptr)
		{
			_baseCollider = dynCollider;
		
			for (auto dynColliderChild : dynCollider->Children)
			{
				if (setMeshChild(dynColliderChild)) return;
			}
		}

		setMeshChild(child);
	}
}

Projectile::ProjectileInfo Projectile::_createProjectile()
{
	if (_baseCollider) return ProjectileInfo{
		.instance = nullptr,
		.lifetime = 0.0f
	};

	auto newCollider = _physics->CreateDynamicCollider();
	newCollider->SetAngularDamping(_baseCollider->GetAngularDamping());
	newCollider->SetDynamicFriction(_baseCollider->GetDynamicFriction());
	newCollider->SetLinearDamping(_baseCollider->GetLinearDamping());
	newCollider->SetMass(_baseCollider->GetMass());
	newCollider->SetMaxAngularVelocity(_baseCollider->GetMaxAngularVelocity());
	newCollider->SetRestitution(_baseCollider->GetRestitution());
	newCollider->SetStaticFriction(_baseCollider->GetStaticFriction());

	for (auto& child : _baseCollider->Children)
	{
		if (auto box = dynamic_cast<Engine3DRadSpace::Objects::Box*>(child); box != nullptr)
		{
			newCollider->AttachShape(box->GetBoundingBox());
		}
		else if (auto sphere = dynamic_cast<Engine3DRadSpace::Objects::Sphere*>(child); sphere != nullptr)
		{
			newCollider->AttachShape(BoundingSphere(sphere->Position, sphere->Radius));
		}
	}
}

void Projectile::Update()
{
	if (Enabled && _projectiles.size() < static_cast<size_t>(MaxProjectiles))
	{
		auto projectile = _createProjectile();
		auto dynProj = projectile.instance;
		dynProj->SetPosition(Position);
		dynProj->AddLinearVelocity(GetDirection());
		_projectiles.emplace_back(projectile);

		Enabled = false;
	}

	auto dt = static_cast<Game*>(GetGame())->Update_dt;

	for (auto p : _projectiles)
	{
		p.lifetime -= dt;

		if (p.lifetime <= 0.0f && p.instance != nullptr)
		{
			_physics->Remove(p.instance);

			p.lifetime = 0.0f;
			p.instance = nullptr;
		}
	}
}

void Projectile::Load()
{
}

void Projectile::Load(const std::filesystem::path& path)
{
}

Reflection::UUID Projectile::GetUUID() const noexcept
{
	// {9447BE3F-2290-4367-99D4-531D5076D773}
	return { 0x9447be3f, 0x2290, 0x4367, { 0x99, 0xd4, 0x53, 0x1d, 0x50, 0x76, 0xd7, 0x73 } };
}

Objects::Gizmos::IGizmo* Projectile::GetGizmo() const noexcept
{
	return nullptr;
}

void Projectile::Draw3D()
{
	if (_baseMesh == nullptr) return;
	
	for (auto& p : _projectiles)
	{
		if (p.lifetime > 0.0f && p.instance != nullptr)
		{
			_baseMesh->Visible = true;
			_baseMesh->Position = p.instance->GetPosition();
			_baseMesh->Rotation = p.instance->GetRotation();
			_baseMesh->Scale = Vector3::One();
			_baseMesh->Draw3D();
		}
	}
}

float Projectile::Intersects(const Math::Ray& r) const
{
	return std::numeric_limits<float>::signaling_NaN();
}

Vector3 Projectile::GetDirection() const noexcept
{
	return Vector3::Transform(Vector3::Forward(), Rotation);
}

float Projectile::GetLifetime(size_t id) const
{
	return _projectiles[id].lifetime;
}

Physics::IDynamicCollider* Projectile::operator[](size_t idxProjectile) const
{
	return _projectiles[idxProjectile].instance;
}

REFL_BEGIN(Projectile, "Projectile", "Physics", "Represents an projectile spawner that can be activated")
REFL_FIELD(Projectile, std::string, Name, "Name", "Projectile", "Name of the object")
REFL_FIELD(Projectile, float, Power, "Power", 10.0f, "Velocity given to a freshly spawned projectile")
REFL_FIELD(Projectile, float, Lifetime, "Lifetime(s)", 5.0f, "How long an projectile exists in the world before it is destroyed")
REFL_FIELD(Projectile, int, MaxProjectiles, "Max number of projectiles", 50, "Maximum number of projectiles that can exist simultaneously in the scene")
REFL_METHOD(Projectile, void, &Projectile::Enable, "Fire")
REFL_METHOD(Projectile, float, &Projectile::GetLifetime, "Lifetime of projectile ID", size_t)
REFL_ATTR("Icon", "Data\\Editor\\OBJ_Projectile.png")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Projectile.html")
REFL_END