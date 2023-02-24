#include "Camera.hpp"

using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

Camera::Camera(const std::string& name,const std::string &tag, bool visible, Vector3 pos, Vector3 look_at, Vector3 up,float aspectRatio, float fov, float npd, float fpd):
	IObject(name,"...","[NO_RESOURCE]", visible, true, pos, Vector3::Zero(), Quaternion(), Vector3::One()),
	FieldOfView(fov),
	FarPlaneDistance(fpd),
	NearPlaneDistance(npd)
{
	SetLookAt(look_at);
}

void Camera::SetLookAt(const Vector3& lookAt)
{
	Vector3 nlk = (Position - lookAt).Normalize();
	this->Rotation = Quaternion::FromAxisAngle(nlk, 0);
}

void Engine3DRadSpace::Objects::Camera::Initialize() 
{

}

void Engine3DRadSpace::Objects::Camera::Draw(Engine3DRadSpace::Math::Matrix& view, Engine3DRadSpace::Math::Matrix& projection, double dt)
{
	view = Matrix::CreateLookAtView(Position, Vector3::UnitZ().Transform(Rotation), UpwardsDir);
	projection = Matrix::CreatePerspectiveProjection(0, FieldOfView, NearPlaneDistance, FarPlaneDistance);
}

void Engine3DRadSpace::Objects::Camera::Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt) { } //Do nothing

void Engine3DRadSpace::Objects::Camera::EditorDraw(const Engine3DRadSpace::Math::Matrix& view, const Engine3DRadSpace::Math::Matrix& projection, double dt)
{
	//TODO: draw 3d camera model
}
