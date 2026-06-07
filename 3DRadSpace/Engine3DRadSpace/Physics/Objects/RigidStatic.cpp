#include "RigidStatic.hpp"
#include "../../Games/Game.hpp"
#include "../../Content/Assets/ModelAsset.hpp"
#include "../../Objects/Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

RigidStatic::RigidStatic(
	const std::string& name,
	bool enabled,
	bool visible, 
	const std::filesystem::path& path,
	const Vector3 position,
	const Quaternion& rotation,
	const Vector3& scale
) : IPhysicsObject(name, enabled, visible, position, rotation, scale)
{
	_path = std::make_unique<std::string>(path.string());
}

RigidStatic::RigidStatic() : RigidStatic("RigidStatic", false, false, "")
{
	_path.reset();
}

float RigidStatic::GetLinearDamping() const noexcept
{
	if(_collider) return _collider->GetLinearDamping();
	return _properties->linearDamping;
}

void RigidStatic::SetLinearDamping(float linearDamping)
{
	if(_collider) _collider->SetLinearDamping(linearDamping);
	else _properties->linearDamping = linearDamping;
}

float RigidStatic::GetStaticFriction() const noexcept
{
	if(_collider) return _collider->GetStaticFriction();
	return _properties->staticFriction;
}

void RigidStatic::SetStaticFriction(float friction)
{
	if(_collider) _collider->SetStaticFriction(friction);
	else _properties->staticFriction = friction;
}

float RigidStatic::GetDynamicFriction() const noexcept
{
	if(_collider) return _collider->GetDynamicFriction();
	return _properties->dynamicFriction;
}

void RigidStatic::SetDynamicFriction(float friction)
{
	if(_collider) _collider->SetDynamicFriction(friction);
	else _properties->dynamicFriction = friction;
}

float RigidStatic::GetRestitution() const noexcept
{
	if(_collider) return _collider->GetRestitution();
	return _properties->restitution;
}

void RigidStatic::SetRestitution(float restitution)
{
	if(_collider) _collider->SetRestitution(restitution);
	else _properties->restitution = restitution;
}

void RigidStatic::Initialize()
{
	IPhysicsObject::Initialize();
}

void RigidStatic::Load()
{
	auto game = static_cast<Game*>(GetGame());

	if(_path)
	{
		_model = game->Content->Load<ModelAsset>(*_path)->Get();
		_collider = _physics->CreateStaticCollider(_model, Position, Rotation, Scale);

		_path.reset();
	}
	if(Model)
	{
		_model = const_cast<Model3D*>((*game->Content)[Model]->Get());
		_collider = _physics->CreateStaticCollider(_model, Position, Rotation, Scale);
	}

	if(_collider && _properties)
	{
		_collider->SetLinearDamping(_properties->linearDamping);
		_collider->SetStaticFriction(_properties->staticFriction);
		_collider->SetDynamicFriction(_properties->dynamicFriction);
		_collider->SetRestitution(_properties->restitution);
		_properties.reset();
	}
}

void RigidStatic::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(GetGame());
	_model = game->Content->Load<ModelAsset>(*_path)->Get();
	_collider = _physics->CreateStaticCollider(_model, Scale);

	if(_collider && _properties)
	{
		_collider->SetLinearDamping(_properties->linearDamping);

		_collider->SetStaticFriction(_properties->staticFriction);
		_collider->SetDynamicFriction(_properties->dynamicFriction);
		_collider->SetRestitution(_properties->restitution);
		_properties.reset();
	}
}

void RigidStatic::Update()
{
	if(_collider != nullptr && _reqTransformUpdate)
	{
		_collider->UpdateTransform(Position, Rotation);
		_reqTransformUpdate = false;
	}
}

void RigidStatic::Draw3D()
{
	auto game = static_cast<Game*>(_game);

	if(Visible && _model)
		_model->Draw(GetModelMatrix() * game->View * game->Projection);
}

float RigidStatic::Intersects(const Math::Ray& r)
{
	if(_collider == nullptr) return std::numeric_limits<float>::signaling_NaN();
	return _collider->Intersects(r).value_or(std::numeric_limits<float>::signaling_NaN());
}

Reflection::UUID RigidStatic::GetUUID() const noexcept
{
	// {11E67CA3-19A3-4558-8528-72A03F0901F9}
	return {0x11e67ca3, 0x19a3, 0x4558, { 0x85, 0x28, 0x72, 0xa0, 0x3f, 0x9, 0x1, 0xf9 }};
}

Model3D* RigidStatic::GetModel() const noexcept
{
	return _model;
}

void RigidStatic::RequestTransformUpdate()
{
	_reqTransformUpdate = true;
}

template<>
class Engine3DRadSpace::Objects::Gizmos::Gizmo<RigidStatic> final : public Engine3DRadSpace::Objects::Gizmos::IGizmo
{
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
		if(!Object) return;
		if(!Object->Visible) return;

		auto rigidStatic = dynamic_cast<RigidStatic*>(Object);
		if(rigidStatic == nullptr) return;
		if(rigidStatic->GetModel() == nullptr) return;

		rigidStatic->Draw3D();
	}

	void Draw2D() override
	{
	}

	void Load() override
	{
		if(Object == nullptr) return;

		Object->Initialize();
		Object->Load();
	}

	void Load(const std::filesystem::path& path) override
	{
		if(Object == nullptr) return;

		Object->Initialize();
		Object->Load(path);
	}

	void Update() override
	{
		//Unlike Dynamic objects: update in case the user changed it in the editor
		auto rs = dynamic_cast<RigidStatic*>(Object);
		if(rs == nullptr) return;

		rs->RequestTransformUpdate();
		rs->Update();
	}

	~Gizmo() = default;
};

Gizmos::IGizmo* RigidStatic::GetGizmo() const noexcept
{
	return Internal::GizmoOf<RigidStatic>(this);
}

IStaticCollider* RigidStatic::GetCollider() const noexcept
{
	return _collider.get();
}

static float rigidstatic_getLinearDamping(RigidStatic& obj)
{
	return obj.GetLinearDamping();
}

static void rigidStatic_setLinearDamping(RigidStatic& obj, const float &value)
{
	obj.SetLinearDamping(value);
}

static float rigidstatic_getStaticFriction(RigidStatic& obj)
{
	return obj.GetStaticFriction();
}

static void rigidStatic_setStaticFriction(RigidStatic& obj, const float &value)
{
	obj.SetStaticFriction(value);
}

static float rigidstatic_getDynamicFriction(RigidStatic& obj)
{
	return obj.GetDynamicFriction();
}

static void rigidStatic_setDynamicFriction(RigidStatic& obj, const float &value)
{
	obj.SetDynamicFriction(value);
}

static float rigidstatic_getRestitution(RigidStatic& obj)
{
	return obj.GetRestitution();
}

static void rigidStatic_setRestitution(RigidStatic& obj, const float &value)
{
	obj.SetRestitution(value);
}

REFL_BEGIN(RigidStatic, "Rigidbody(Static)", "Physics", "Static rigidbody based off an mesh collider")
REFL_FIELD(RigidStatic, std::string, Name, "Name", "RigidStatic", "Name of the object")
REFL_FIELD(RigidStatic, bool, Enabled, "Enabled", true, "Whether the object is enabled or not")
REFL_FIELD(RigidStatic, bool, Visible, "Visible", true, "Whether the object is visible or not")
REFL_FIELD(RigidStatic, RefModel3D, Model, "Model", 0, "Model used for rendering and collision")
REFL_FIELD(RigidStatic, Vector3, Position, "Position", Vector3::Zero(), "Position of the object")
REFL_FIELD(RigidStatic, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation of the object")
REFL_FIELD(RigidStatic, Vector3, Scale, "Scale", Vector3::One(), "Scale of the object (Only used at initialization!)")
REFL_FIELD_GS(RigidStatic, float, rigidstatic_getLinearDamping, rigidStatic_setLinearDamping, "Linear Damping", 0.0f, "Linear damping coefficient")
REFL_FIELD_GS(RigidStatic, float, rigidstatic_getStaticFriction, rigidStatic_setStaticFriction, "Static Friction", 0.5f, "Static friction of the material")
REFL_FIELD_GS(RigidStatic, float, rigidstatic_getDynamicFriction, rigidStatic_setDynamicFriction, "Dynamic Friction", 0.5f, "Dynamic friction of the material")
REFL_FIELD_GS(RigidStatic, float, rigidstatic_getRestitution, rigidStatic_setRestitution, "Restitution", 0.5f, "Bounciness of the material")
REFL_END