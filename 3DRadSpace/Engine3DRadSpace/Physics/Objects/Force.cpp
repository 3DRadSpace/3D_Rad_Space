#include "Force.hpp"
#include "../../Games/Game.hpp"
#include "RigidDynamic.hpp"
#include "FPCharacter.hpp"
#include "../../Objects/Gizmos/Gizmo.hpp"
#include "../../Objects/Gizmos.hpp"
#include "../../Graphics/Primitives/Arrow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

Force::Force(
	const std::string& name,
	const Vector3& position,
	const Quaternion& rotation,
	float magnitude,
	float timer,
	bool torque
) : IPhysicsObject(name, true, true, position, rotation, Vector3::One()),
	Magnitude(magnitude), 
	Timer(timer), Torque(torque)
{
	_direction = Vector3::Forward().Transform(rotation);
}

void Force::Enable()
{
	_time = Timer;
}

void Force::Disable()
{
	_time = 0;
}

void Force::Load()
{
}

void Force::Load(const std::filesystem::path& path)
{
}

void Force::Update()
{
	auto game = static_cast<Game*>(GetGame());

	if (_time > 0)
	{
		auto dt = game->Update_dt;
		_time -= dt;

		if (RigidDynamic* parent = static_cast<RigidDynamic*>(_parent); parent != nullptr)
		{
			if(!Torque)
				parent->SetLinearVelocity(parent->GetLinearVelocity() + Direction() * Magnitude * dt);
			else
				parent->SetAngularVelocity(parent->GetAngularVelocity() + Direction() * Magnitude * dt);
		}

		if (FPCharacter* parent = static_cast<FPCharacter*>(_parent); parent != nullptr)
		{
			if (!Torque)
				parent->Position += Direction() * Magnitude * dt;
			else
			{
				Vector3 axis = Direction().Normalize();
				float angle = Magnitude * dt;
				Quaternion delta = Quaternion::FromAxisAngle(axis, angle);
				parent->Rotation = (parent->Rotation * delta).Normalize();
			}
		}
	}
}

void Force::Draw3D()
{
}

Vector3 Force::Direction() const noexcept
{
	return _direction;
}

float Force::Intersects(const Ray& r)
{
	return std::numeric_limits<float>::quiet_NaN();
}

Reflection::UUID Force::GetUUID() const noexcept
{
	// {D8826FCB-E3A3-4887-94B2-ADF0C094F2ED}
	return { 0xd8826fcb, 0xe3a3, 0x4887, { 0x94, 0xb2, 0xad, 0xf0, 0xc0, 0x94, 0xf2, 0xed } };
}

template<>
class Engine3DRadSpace::Objects::Gizmos::Gizmo<Force> final : public Engine3DRadSpace::Objects::Gizmos::IGizmo
{
	std::unique_ptr<Arrow> _arrow;
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
		if (!Object) return;

		auto f = dynamic_cast<Force*>(Object);
		if (f == nullptr) return;

		_arrow->Transform = f->GetModelMatrix();
		
		auto g = static_cast<Game*>(Object->GetGame());
		_arrow->View = g->View;
		_arrow->Projection = g->Projection;

		_arrow->Draw3D();
	}

	void Draw2D() override
	{
	}

	void Load() override
	{
		if (Object == nullptr) return;

		if (_arrow) return;

		_arrow = std::make_unique<Arrow>(
			Object->GetGraphicsDeviceHandle(),
			Vector2(0.0625f, 1.0f),
			Colors::Orange
		);
	}

	void Load(const std::filesystem::path& path) override
	{
	}

	void Update() override
	{
	}

	~Gizmo() = default;
};

Engine3DRadSpace::Objects::Gizmos::IGizmo* Force::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Force>(this);
}

REFL_BEGIN(Force, "Force", "Physics", "Applies a force to a physics object when enabled")
REFL_FIELD(Force, std::string, Name, "Name", "Force", "Name of the object")
REFL_FIELD(Force, Vector3, Position, "Position", Vector3(), "Position of the force (usually offset from the object")
REFL_FIELD(Force, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation of the force")
REFL_FIELD(Force, float, Magnitude, "Magnitude", 1.0f, "Strength of the force")
REFL_FIELD(Force, float, Timer, "Time", 1.0f, "Duration of the force in seconds")
REFL_FIELD(Force, bool, Torque, "Torque", false, "Whether the force is a torque (applies rotation) or a linear force")
REFL_METHOD(Force, void, &Force::Enable, "Enable")
REFL_METHOD(Force, void, &Force::Disable, "Disable")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Force.html")
REFL_END