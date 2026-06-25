#include "RigidDynamic.hpp"
#include "../../Objects/Impl/Box.hpp"
#include "../../Objects/Impl/Sphere.hpp"
#include "../../Objects/Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;
using namespace Engine3DRadSpace::Objects;

RigidDynamic::RigidDynamic(
	const std::string& name,
	bool enabled,
	bool visible,
	const Math::Vector3& position,
	const Math::Quaternion& rotation,
	const Math::Vector3& scale
) : IPhysicsObject(name, enabled, visible, position, rotation, scale)
{
}

float RigidDynamic::GetMass() const noexcept
{
	if(_collider) return _collider->GetMass();
	return _properties->mass;
}

void RigidDynamic::SetMass(float mass)
{
	if(_collider) _collider->SetMass(mass);
	else _properties->mass = mass;
}

float RigidDynamic::GetLinearDamping() const noexcept
{
	if(_collider) return _collider->GetLinearDamping();
	return _properties->linearDamping;
}

void RigidDynamic::SetLinearDamping(float linearDamping)
{
	if(_collider) _collider->SetLinearDamping(linearDamping);
	else _properties->linearDamping = linearDamping;
}

float RigidDynamic::GetAngularDamping() const noexcept
{
	if(_collider) return _collider->GetAngularDamping();
	return _properties->angularDamping;
}

void RigidDynamic::SetAngularDamping(float angularDamping)
{
	if(_collider) _collider->SetAngularDamping(angularDamping);
	else _properties->angularDamping = angularDamping;
}

float RigidDynamic::GetStaticFriction() const noexcept
{
	if(_collider) return _collider->GetStaticFriction();
	return _properties->staticFriction;
}

void RigidDynamic::SetStaticFriction(float friction)
{
	if(_collider) _collider->SetStaticFriction(friction);
	else _properties->staticFriction = friction;
}

float RigidDynamic::GetDynamicFriction() const noexcept
{
	if(_collider) return _collider->GetDynamicFriction();
	return _properties->dynamicFriction;
}

void RigidDynamic::SetDynamicFriction(float friction)
{
	if(_collider) _collider->SetDynamicFriction(friction);
	else _properties->dynamicFriction = friction;
}

float RigidDynamic::GetRestitution() const noexcept
{
	if(_collider) return _collider->GetRestitution();
	return _properties->restitution;
}

void RigidDynamic::SetRestitution(float restitution)
{
	if(_collider) _collider->SetRestitution(restitution);
	else _properties->restitution = restitution;
}

Math::Vector3 RigidDynamic::GetLinearVelocity() const noexcept
{
	if(_collider) return _collider->GetLinearVelocity();
	return _properties->linearVelocity;
}

void RigidDynamic::SetLinearVelocity(const Math::Vector3& linearVelocity)
{
	if(_collider) _collider->SetLinearVelocity(linearVelocity);
	else _properties->linearVelocity = linearVelocity;
}

Math::Vector3 RigidDynamic::GetAngularVelocity() const noexcept
{
	if(_collider) return _collider->GetAngularVelocity();
	return _properties->angularVelocity;
}

void RigidDynamic::SetAngularVelocity(const Math::Vector3& angularVelocity)
{
	if(_collider) _collider->SetAngularVelocity(angularVelocity);
	else _properties->angularVelocity = angularVelocity;
}

Math::Vector3 RigidDynamic::GetMaxAngularVelocity() const noexcept
{
	if(_collider) return _collider->GetMaxAngularVelocity();
	return _properties->maxAngularVelocity;
}

void RigidDynamic::SetMaxAngularVelocity(const Math::Vector3& maxAngularVelocity)
{
	if(_collider) _collider->SetMaxAngularVelocity(maxAngularVelocity);
	else _properties->maxAngularVelocity = maxAngularVelocity;
}

void RigidDynamic::Initialize()
{
	IPhysicsObject::Initialize();
	_collider = _physics->CreateDynamicCollider();
	
	if(Children.Count() == 0)
	{
		Enabled = false;
	}

	for(auto& child : Children)
	{
		if(child == nullptr) continue;

		bool isShape = false;

		if(dynamic_cast<Engine3DRadSpace::Objects::Box*>(child) != nullptr)
		{
			isShape = true;

			auto box = dynamic_cast<Engine3DRadSpace::Objects::Box*>(child);
			Math::BoundingBox bbox(box->Position, box->Scale);

			_collider->AttachShape(bbox);
		}

		if(dynamic_cast<Engine3DRadSpace::Objects::Sphere*>(child) != nullptr)
		{
			isShape = true;
			auto sphere = dynamic_cast<Engine3DRadSpace::Objects::Sphere*>(child);
			Math::BoundingSphere sph(sphere->Position, sphere->Radius);

			_collider->AttachShape(sph);
		}

		if(isShape)
		{
			child->Visible = false;
			child->Enabled = false;
		}
	}

	if(_properties)
	{
		_collider->SetMass(_properties->mass);
		_collider->SetLinearDamping(_properties->linearDamping);
		_collider->SetAngularDamping(_properties->angularDamping);
		_collider->SetStaticFriction(_properties->staticFriction);
		_collider->SetDynamicFriction(_properties->dynamicFriction);
		_collider->SetRestitution(_properties->restitution);
		_collider->SetLinearVelocity(_properties->linearVelocity);
		_collider->SetAngularVelocity(_properties->angularVelocity);
		_collider->SetMaxAngularVelocity(_properties->maxAngularVelocity);

		_properties.reset();
	}

	// Update mass and inertia after all shapes are attached
	_collider->UpdateMassAndInertia();

	_collider->UpdateTransform(Position, Rotation);
}

void RigidDynamic::Load()
{
}

void RigidDynamic::Load(const std::filesystem::path& path)
{
}

void RigidDynamic::Update()
{
	if (_collider)
	{
		Position = _collider->GetPosition();
		Rotation = _collider->GetRotation();
	}
}

void RigidDynamic::Draw3D()
{
}

void RigidDynamic::Teleport(const Math::Vector3& position, const std::optional<Math::Quaternion>& rotation)
{
	_collider->UpdateTransform(position, Rotation);
}

float RigidDynamic::Intersects(const Math::Ray& r)
{
	constexpr float nan = std::numeric_limits<float>::signaling_NaN();

	if(_collider == nullptr) return nan;
	return _collider->Intersects(r).value_or(nan);
}

Reflection::UUID RigidDynamic::GetUUID() const noexcept
{
	// {E360B70E-266C-4B9B-A14C-62979B930D3C}
	return {0xe360b70e, 0x266c, 0x4b9b, { 0xa1, 0x4c, 0x62, 0x97, 0x9b, 0x93, 0xd, 0x3c }};
}

template<>
class Engine3DRadSpace::Objects::Gizmos::Gizmo<RigidDynamic> final : public Engine3DRadSpace::Objects::Gizmos::IGizmo
{
	bool _wasLoaded = false;
public:
	Gizmo()
	{
		Allow3DRendering = true;
		Allow2DRendering = false;
		AllowScaling = false;
		AllowRotating = true;
		AllowTranslating = true;
	}

	void Draw3D() override
	{
	}

	void Draw2D() override
	{
	}

	void Load() override
	{
	}

	void Load(const std::filesystem::path& path) override
	{
	}

	void Update() override
	{
	}

	~Gizmo() = default;
};

Gizmos::IGizmo* RigidDynamic::GetGizmo() const noexcept
{
	return Internal::GizmoOf<RigidDynamic>(this);
}

void RigidDynamic::SetKinematic(bool isKinematic)
{
	_kinematic = isKinematic;
	if(_collider) _collider->SetKinematic(isKinematic);
}

bool RigidDynamic::IsKinematic() const noexcept
{
	return _kinematic;
}

static bool rigiddyn_getkinematic(RigidDynamic& rd) { return rd.IsKinematic(); }
static void rigiddyn_setkinematic(RigidDynamic& rd, const bool& isKinematic) { rd.SetKinematic(isKinematic); }

static float rigiddyn_getmass(RigidDynamic& rd) { return rd.GetMass(); }
static void rigiddyn_setmass(RigidDynamic& rd, const float &mass) { rd.SetMass(mass); }

static float rigiddyn_getlineardamping(RigidDynamic& rd) { return rd.GetLinearDamping(); }
static void rigiddyn_setlineardamping(RigidDynamic& rd, const float& linearDamping) { rd.SetLinearDamping(linearDamping); }

static float rigiddyn_getangulardamping(RigidDynamic& rd) { return rd.GetAngularDamping(); }
static void rigiddyn_setangulardamping(RigidDynamic& rd, const float& angularDamping) { rd.SetAngularDamping(angularDamping); }

static float rigiddyn_getstaticfriction(RigidDynamic& rd) { return rd.GetStaticFriction(); }
static void rigiddyn_setstaticfriction(RigidDynamic& rd, const float& staticFriction) { rd.SetStaticFriction(staticFriction); }

static float rigiddyn_getdynamicfriction(RigidDynamic& rd) { return rd.GetDynamicFriction(); }
static void rigiddyn_setdynamicfriction(RigidDynamic& rd, const float& dynamicFriction) { rd.SetDynamicFriction(dynamicFriction); }

static float rigiddyn_getrestitution(RigidDynamic& rd) { return rd.GetRestitution(); }
static void rigiddyn_setrestitution(RigidDynamic& rd, const float& restitution) { rd.SetRestitution(restitution); }

REFL_BEGIN(RigidDynamic, "RigidDynamic", "Physics", "A physics object with dynamic rigidbody colliders")
REFL_FIELD(RigidDynamic, std::string, Name, "Name", "RigidDynamic", "Object of the name")
REFL_FIELD(RigidDynamic, bool, Enabled, "Enabled", true, "Is the physics object active?")
REFL_FIELD(RigidDynamic, Math::Vector3, Position, "Position", Math::Vector3::Zero(), "World position of the physics object")
REFL_FIELD(RigidDynamic, Math::Quaternion, Rotation, "Rotation", Math::Quaternion(), "World rotation of the physics object")
REFL_FIELD_GS(RigidDynamic, bool, rigiddyn_getkinematic, rigiddyn_setkinematic, "Kinematic", false, "Is the rigidbody kinematic?")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getmass, rigiddyn_setmass, "Mass", 1.0f, "Mass of the rigidbody")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getlineardamping, rigiddyn_setlineardamping, "Linear Damping", 0.0f, "Linear damping coefficient")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getangulardamping, rigiddyn_setangulardamping, "Angular Damping", 0.05f, "Angular damping coefficient")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getstaticfriction, rigiddyn_setstaticfriction, "Static Friction", 0.5f, "Static friction of the material")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getdynamicfriction, rigiddyn_setdynamicfriction, "Dynamic Friction", 0.5f, "Dynamic friction of the material")
REFL_FIELD_GS(RigidDynamic, float, rigiddyn_getrestitution, rigiddyn_setrestitution, "Restitution", 0.5f, "Bounciness of the material")
REFL_END