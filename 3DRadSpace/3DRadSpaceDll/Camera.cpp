#include "Camera.hpp"

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

Engine3DRadSpace::Camera::~Camera()
{
}
