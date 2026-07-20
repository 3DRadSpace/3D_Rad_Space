#include "FPCharacter.hpp"
#include "../../Games/Game.hpp"
#include "../ICharacterController.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Physics;
using namespace Engine3DRadSpace::Physics::Objects;

FPCharacter::FPCharacter(
	const std::string& name,
	bool visible,
	const Math::Vector3& pos,
	const Math::Quaternion& rotation,
	const Math::Vector3& up,
	float aspectRatio,
	float fov,
	float npd,
	float fpd
) : FreeCam(name, visible, pos, rotation, up, aspectRatio, fov, npd, fpd),
	_physics(nullptr)
{
}

void FPCharacter::Initialize()
{
	FreeCam::Initialize();
	_physics = _game->RequireService<IPhysicsEngine>({});
	_controller = _physics->CreateCharacterController(Radius, Height, Position);
}

void FPCharacter::Update()
{
	if (!Enabled)
	{
		Camera::Update();
		return;
	}
	if (!_controller) return;

	Game* game = static_cast<Game*>(_game);
	float dt = game->Update_dt;

	auto screenCenter = game->Window->Size() / 2;
	Math::Point mousePos = game->Mouse.Position();
	game->Window->SetMousePosition(screenCenter);

	auto mouseDelta = (Math::Vector2)(mousePos - screenCenter);

	float invertX = InvertX ? -1.0f : 1.0f;
	float invertY = InvertY ? -1.0f : 1.0f;
	_camCoords.X -= mouseDelta.X * Sensitivity * dt * invertX;
	_camCoords.Y -= mouseDelta.Y * Sensitivity * dt * invertY;

	_camCoords.Y = std::clamp<float>(
		_camCoords.Y,
		-std::numbers::pi_v<float> / 2.f + 0.001f,
		std::numbers::pi_v<float> / 2.f - 0.001f
	);

	Rotation = Math::Quaternion::FromYawPitchRoll(_camCoords.X, _camCoords.Y, 0);

	_fwd = Math::Vector3::Transform(-Math::Vector3::UnitZ(), Rotation);

	Math::Vector3 horizFwd = _fwd - Normal * Math::Vector3::Dot(_fwd, Normal);
	if (horizFwd.LengthSquared() > 0.0f) horizFwd.Normalize();

	Math::Vector3 right = Math::Vector3::Normalize(Math::Vector3::Cross(horizFwd, Normal));

	_dir = Math::Vector3::Zero();

	auto& kb = game->Keyboard;

	if (kb.IsKeyDown(Forward))  _dir += horizFwd;
	if (kb.IsKeyDown(Backward)) _dir -= horizFwd;
	if (kb.IsKeyDown(Left))     _dir -= right;
	if (kb.IsKeyDown(Right))    _dir += right;

	if (_dir.LengthSquared() > 0) _dir.Normalize();

	if (!Frozen)
	{
		_controller->Move(_dir * MovementSpeed * dt);

		if (kb.IsKeyDown(Jump))
			_controller->Jump(JumpPower);
	}

	_controller->UpdateTransform();
	Position = _controller->GetPosition();
	Camera::Update();
}

void FPCharacter::Teleport(const Math::Vector3& position)
{
	_controller->SetPosition(position);
	Position = position;
}

void FPCharacter::Teleport(const Math::Vector3& position, const Math::Quaternion& rotation)
{
	_controller->SetPosition(position);
	_controller->SetRotation(rotation);

	Position = position;
	Rotation = rotation;
}

Reflection::UUID FPCharacter::GetUUID() const noexcept
{
	// {AC8F8DF7-80EC-4293-A78B-DE7F3FFFBF49}
	return { 0xac8f8df7, 0x80ec, 0x4293, { 0xa7, 0x8b, 0xde, 0x7f, 0x3f, 0xff, 0xbf, 0x49 } };
}

ICharacterController* FPCharacter::GetController() const noexcept
{
	return _controller.get();
}

void FPCharacter::Draw3D()
{
	if(!Visible) return;

	auto game = static_cast<Game*>(_game);
	game->View = GetViewMatrix();
	game->Projection = GetProjectionMatrix();
	
	Camera::Update();
}

Math::Matrix4x4 FPCharacter::GetViewMatrix() const noexcept
{
	Vector3 camPos = Vector3(Position.X, Position.Y + Height, Position.Z);
	Vector3 focus = camPos + Vector3::Forward().Transform(Rotation);
	return Matrix4x4::CreateLookAtView(camPos, focus, Normal);
}

REFL_BEGIN(FPCharacter, "First Person Character", "Physics", "A first person character controller")
REFL_FIELD(FPCharacter, std::string, Name, "Name", "FPCharacter", "Name of the object")
REFL_FIELD(FPCharacter, bool, Enabled, "Enabled", true, "Whether the object is enabled or not")
REFL_FIELD(FPCharacter, bool, Frozen, "Frozen", false, "Whether movement is enabled")
REFL_FIELD(FPCharacter, Vector3, Position, "Position", Vector3::Zero(), "Position of the object")
REFL_FIELD(FPCharacter, Quaternion, Rotation, "Rotation", Quaternion(), "Rotation of the object")
REFL_FIELD(FPCharacter, Vector3, Normal, "Normal", Vector3::UnitY(), "Camera surface normal vector")
REFL_FIELD(FPCharacter, float, Radius, "Radius", 0.5f, "Radius of the character's capsule collider")
REFL_FIELD(FPCharacter, float, Height, "Height", 1.8f, "Height of the character's capsule collider")
REFL_FIELD(FPCharacter, float, MovementSpeed, "Movement Speed", 1.0f, "Movement speed of the character")
REFL_FIELD(FPCharacter, float, JumpPower, "Jump Power", 1.0f, "Jump power of the character")
REFL_FIELD(FPCharacter, Input::Key, Forward, "Forward Key", Input::Key::W, "Key used for moving forward")
REFL_FIELD(FPCharacter, Input::Key, Backward, "Backward Key", Input::Key::S, "Key used for moving backward")
REFL_FIELD(FPCharacter, Input::Key, Left, "Left Key", Input::Key::A, "Key used for moving left")
REFL_FIELD(FPCharacter, Input::Key, Right, "Right Key", Input::Key::D, "Key used for moving right")
REFL_FIELD(FPCharacter, Input::Key, Jump, "Jump Key", Input::Key::Space, "Key used for jumping")
REFL_FIELD(FPCharacter, float, Sensitivity, "Mouse Sensitivity", 0.1f, "Mouse sensitivity for looking around")
REFL_FIELD(FPCharacter, bool, InvertX, "Invert X", false, "Whether to invert the X axis for looking around")
REFL_FIELD(FPCharacter, bool, InvertY, "Invert Y", false, "Whether to invert the Y axis for looking around")
REFL_FIELD(FPCharacter, float, AspectRatio, "Aspect Ratio", 4.0f / 3.0f, "Aspect ratio of the camera")
REFL_FIELD(FPCharacter, float, FieldOfView, "Field of View", Math::ToRadians(65.0f), "Field of view of the camera")
REFL_FIELD(FPCharacter, float, NearPlaneDistance, "Near Plane Distance", 0.01f, "Near plane distance of the camera")
REFL_FIELD(FPCharacter, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
REFL_METHOD(FPCharacter, void, &FPCharacter::Enable, "Enable")
REFL_METHOD(FPCharacter, void, &FPCharacter::Disable, "Disable")
REFL_METHOD(FPCharacter, bool, &FPCharacter::Switch, "Switch")
REFL_METHOD(FPCharacter, void, &FPCharacter::Show, "Show")
REFL_METHOD(FPCharacter, void, &FPCharacter::Hide, "Hide")
REFL_METHOD(FPCharacter, bool, &FPCharacter::SwitchVisibility, "Switch visibility")
REFL_METHOD(FPCharacter, Matrix4x4, &FPCharacter::GetModelMatrix, "Get World Matrix")
REFL_METHOD(FPCharacter, Matrix4x4, &FPCharacter::GetViewMatrix, "Get View Matrix")
REFL_METHOD(FPCharacter, Matrix4x4, &FPCharacter::GetProjectionMatrix, "Get Projection Matrix")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/FPCharacter.html")
REFL_END