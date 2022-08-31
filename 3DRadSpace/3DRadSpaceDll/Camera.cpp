#include "Camera.hpp"

Engine3DRadSpace::Camera::Camera(Game* g,
	const std::string& name = "Camera",
	bool enabled = true,
	const Vector3& pos = Vector3::Zero(),
	const Quaternion& rot = Quaternion(),
	const Vector3& normal = Vector3::UnitY(),
	float fov = Engine3DRadSpace::Math::ToRadians(65.0f),
	float aspect_ratio = 4.f/3.f,
	float npd = 0.01f,
	float fpd = 500) 
	:
	IObject(g, name, enabled, pos, rot),
	Normal(normal), 
	FOV(fov),
	AspectRatio(aspect_ratio),
	NearPlaneDistance(npd),
	FarPlaneDistance(fpd),
	lookat(Vector3::UnitZ()* rot)
{
};

Engine3DRadSpace::Camera::Camera() :
	IObject(),
	Normal(),
	FOV(),
	AspectRatio(),
	NearPlaneDistance(),
	FarPlaneDistance(),
	lookat()
{
};

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetTranslation()
{
	return Engine3DRadSpace::Matrix::CreateTranslation(Position);
}

void Engine3DRadSpace::Camera::Update(float dt)
{
	// we don't do anything here.
}

void Engine3DRadSpace::Camera::Draw(float dt, Game* g)
{
	//we don't do anything here either
}

void Engine3DRadSpace::Camera::Enable()
{
	this->Enabled = true;
}

char* Engine3DRadSpace::Camera::WriteToFileBuffer(size_t& s)
{
	s = 0;
	return nullptr;
}

void Engine3DRadSpace::Camera::SetLookDirection(const Quaternion& q)
{
	this->lookat = Vector3::UnitZ() * q;
}

void Engine3DRadSpace::Camera::SetLookDirection(const Vector3& v)
{
	this->lookat = v;
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetViewMatrix() const
{
	return Engine3DRadSpace::Matrix::CreateLookAt(Position, lookat, Normal);
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetProjectionMatrix() const
{
	return Matrix::CreateProjectionFOV(this->FOV, this->AspectRatio, this->NearPlaneDistance, this->FarPlaneDistance);
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetCameraMatrix() const
{
	return this->GetViewMatrix() * this->GetProjectionMatrix();
}

Engine3DRadSpace::Camera::~Camera()
{
}

using namespace Engine3DRadSpace;
__BEGIN_REFLECTOBJECT(Camera)
	__REFLECTFIELD(Camera, std::string, "Name", Name, "Camera"),
	__REFLECTFIELD(Camera, bool, "Enabled", Enabled, true),
	__REFLECTFIELD(Camera, Vector3, "Position", Position, Vector3::Zero()),
	__REFLECTFIELD(Camera, Quaternion, "Rotation", Rotation, Quaternion()),
	__REFLECTFIELD(Camera, Vector3, "Normal", Normal, Vector3::UnitY()),
	__REFLECTFIELD(Camera, float, "Field of view", FOV, 65),
	__REFLECTFIELD(Camera, float, "Aspect ratio", AspectRatio, 4 / 3),
	__REFLECTFIELD(Camera, float, "Near plane distance", NearPlaneDistance, 0.001f),
	__REFLECTFIELD(Camera, float, "Far plane distance", FarPlaneDistance, 500.0f)
__END_REFLECTOBJECT(Camera)
