#include "Camera.hpp"
#include "../Reflection/Reflection.hpp"

using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

Camera::Camera(const std::string& name,const std::string &tag, bool visible, Vector3 pos, Vector3 look_at, Vector3 up,float aspectRatio, float fov, float npd, float fpd):
	IObject(name,tag, visible, true, pos, Vector3::Zero(), Quaternion(), Vector3::One()),
	UpwardsDir(up),
	AspectRatio(aspectRatio),
	FieldOfView(fov),
	FarPlaneDistance(fpd),
	NearPlaneDistance(npd),
	LookAt(0,0,0),
	LookMode(CameraMode::UseRotation)
{
}

void Engine3DRadSpace::Objects::Camera::Initialize() 
{
}

void Engine3DRadSpace::Objects::Camera::EditorInitialize()
{
	//TODO: Load 3D Camera model.
}

void Engine3DRadSpace::Objects::Camera::Draw(Engine3DRadSpace::Math::Matrix& view, Engine3DRadSpace::Math::Matrix& projection, double dt)
{
	Vector3 focus(0, 0, 0);
	switch (this->LookMode)
	{
	case CameraMode::UseRotation:
		focus = Position + Vector3::UnitZ().Transform(Rotation);
		break;
	case CameraMode::UseLookAtCoordinates:
		focus = this->LookAt;
		break;
	default: //Normally we wouldn't get here. Do not set the focus vector.
		break;
	}
	
	view = Matrix::CreateLookAtView(Position, focus, UpwardsDir);
	projection = Matrix::CreatePerspectiveProjection(AspectRatio, FieldOfView, NearPlaneDistance, FarPlaneDistance);
}

void Engine3DRadSpace::Objects::Camera::Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) { } //Do nothing

void Engine3DRadSpace::Objects::Camera::EditorDraw(const Matrix& view, const Matrix& projection, double dt, bool selected)
{
	//TODO: draw 3d camera model
}

Engine3DRadSpace::Reflection::UUID Engine3DRadSpace::Objects::Camera::GetUUID()
{
	// {84376082-A56E-49E6-B095-BAEEF4BF29B5}
	return {0x84376082, 0xa56e, 0x49e6, { 0xb0, 0x95, 0xba, 0xee, 0xf4, 0xbf, 0x29, 0xb5 }};
}

void Engine3DRadSpace::Objects::Camera::Load(Content::ContentManager *content)
{
}

REFL_BEGIN(Camera,"Camera","Camera objects","Perspective camera")
	REFL_FIELD(Camera, std::string, Name, "Name", "Camera", "Camera's name")
	REFL_FIELD(Camera, bool, Enabled, "Enabled", true, "Does the camera render the scene?")
	REFL_FIELD(Camera, Vector3, Position, "Position", Vector3::Zero(), "Camera position")
	REFL_FIELD(Camera, Quaternion, Rotation, "Rotation", Quaternion(), "Camera rotation")
	REFL_FIELD(Camera, Vector3, UpwardsDir, "Upwards direction", Vector3::One(), "Camera surface normal vector")
	REFL_FIELD(Camera, float, AspectRatio, "Aspect ratio", 4.f / 3.f, "Camera aspect ratio")
	REFL_FIELD(Camera, float, FieldOfView, "Field of view", 65.f, "Camera's field of view")
	REFL_FIELD(Camera, float, NearPlaneDistance, "Near plane distance", 0.01f, "Minimum drawing distance")
	REFL_FIELD(Camera, float, FarPlaneDistance, "Far plane distance", 500.f, "Maximum drawing distance")
REFL_END