#include "FreeCam.hpp"
#include "../../Math/Math.hpp"
#include "../../Games/Game.hpp"
#include "../Gizmos.hpp"
#include "../Gizmos/CameraGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

FreeCam::FreeCam(
	const std::string& name,
	bool enabled,
	const Vector3& pos,
	const Quaternion& rotation,
	const Vector3& up,
	float aspectRatio,
	float fov,
	float npd,
	float fpd
) : Camera(name, enabled, pos, rotation, up, aspectRatio, fov, npd, fpd),
	_camCoords(rotation.ToYawPitchRoll().XY())
{
}

void FreeCam::Update()
{
	if(!Enabled) return;
	if (Frozen)
	{
		Camera::Update();
		return;
	}

	auto game = static_cast<Game*>(_game);
	float dt = game->Update_dt;

	auto screenCenter = game->Window->Size() / 2;
	Point mousePos = game->Mouse.Position();
	game->Window->SetMousePosition(screenCenter);

	auto mouseDelta = (Vector2)(screenCenter - mousePos);
	_camCoords -= mouseDelta * Sensitivity * dt;

	_camCoords.Y = std::clamp<float>(
		_camCoords.Y,
		-std::numbers::pi_v<float> / 2.f + 0.001f,
		std::numbers::pi_v<float> / 2.f - 0.001f
	);

	Rotation = Quaternion::FromYawPitchRoll(_camCoords.X, _camCoords.Y, 0);

	_fwd = Vector3::Transform(-Vector3::UnitZ(), Rotation);
	Vector3 right = Vector3::Normalize(Vector3::Cross(Normal, _fwd));

	auto &kb = game->Keyboard;

	_dir = Vector3::Zero();
	if(kb.IsKeyDown(Forward)) _dir += _fwd;
	if(kb.IsKeyDown(Backward)) _dir -= _fwd;
	if(kb.IsKeyDown(Left)) _dir -= right;
	if(kb.IsKeyDown(Right)) _dir += right;

	if (EnableElevation)
	{
		if (kb.IsKeyDown(Elevate)) _dir += Normal;
		if (kb.IsKeyDown(Descend)) _dir -= Normal;
	}

	if(_dir.LengthSquared() > 0) _dir.Normalize();

	Position += _dir * MovementSpeed * dt;

	Camera::Update();
}

Reflection::UUID FreeCam::GetUUID() const noexcept
{
	// {FDA0C96A-3040-4E5C-B12C-D34577D99415}
	return {0xfda0c96a, 0x3040, 0x4e5c, { 0xb1, 0x2c, 0xd3, 0x45, 0x77, 0xd9, 0x94, 0x15 }};
}

Objects::Gizmos::IGizmo* FreeCam::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Camera>(this);
}

Math::Vector3 FreeCam::ForwardDir() const noexcept
{
	return _fwd;
}

void FreeCam::SetCameraRotation(const Vector2& camCoords) noexcept
{
	_camCoords = camCoords;
	Rotation = Quaternion::FromYawPitchRoll(_camCoords.X, _camCoords.Y, 0);
}

REFL_BEGIN(FreeCam, "FreeCam", "Camera objects", "Perspective camera")
	REFL_FIELD(FreeCam, std::string, Name, "Name", "FreeCam", "Camera's name")
	REFL_FIELD(FreeCam, bool, Enabled, "Enabled", true, "Does the camera render the scene?")
	REFL_FIELD(FreeCam, Vector3, Position, "Position", Vector3::Zero(), "Camera position")
	REFL_FIELD(FreeCam, Quaternion, Rotation, "Rotation", Quaternion(), "Camera rotation")
	REFL_FIELD(FreeCam, Vector3, Normal, "Normal", Vector3::UnitY(), "Camera surface normal vector")
	REFL_FIELD(FreeCam, float, AspectRatio, "Aspect ratio", 4.f / 3.f, "Camera aspect ratio")
	REFL_FIELD(FreeCam, float, FieldOfView, "Field of view", 65.f, "Camera's field of view")
	REFL_FIELD(FreeCam, float, NearPlaneDistance, "Near plane distance", 0.01f, "Minimum drawing distance")
	REFL_FIELD(FreeCam, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
	REFL_FIELD(FreeCam, float, Sensitivity, "Sensitivity", 0.1f, "Mouse sensitivity")
	REFL_FIELD(FreeCam, float, MovementSpeed, "Movement speed", 1.0f, "Noclip camera movement speed")
	REFL_FIELD(FreeCam, bool, InvertX, "Invert X", false, "Invert X Axis")
	REFL_FIELD(FreeCam, bool, InvertY, "Invert Y", false, "Invert Y Axis")
	REFL_FIELD(FreeCam, Input::Key, Forward, "Forward", Input::Key::W, "Forward direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Backward, "Backwards", Input::Key::S, "Backward direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Left, "Left", Input::Key::A, "Left direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Right, "Right", Input::Key::D, "Right direction keybind")
	REFL_FIELD(FreeCam, Input::Key, Elevate, "Elevate", Input::Key::Q, "Elevation keybind")
	REFL_FIELD(FreeCam, Input::Key, Descend, "Descend", Input::Key::E, "Descend keybind")
	REFL_METHOD(FreeCam, void, &Camera::Enable, "Enable")
	REFL_METHOD(FreeCam, void, &Camera::Disable, "Disable")
	REFL_METHOD(FreeCam, bool, &Camera::Switch, "Switch")
	REFL_METHOD(FreeCam, void, &Camera::Show, "Show")
	REFL_METHOD(FreeCam, void, &Camera::Hide, "Hide")
	REFL_METHOD(FreeCam, bool, &Camera::SwitchVisibility, "Switch visibility")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetModelMatrix, "Get World Matrix")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetViewMatrix, "Get View Matrix")
	REFL_METHOD(FreeCam, Matrix4x4, &FreeCam::GetProjectionMatrix, "Get Projection Matrix")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/FreeCam.html")
REFL_END