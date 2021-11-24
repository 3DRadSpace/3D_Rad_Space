#include "Camera.h"

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
	return nullptr;
}

void Engine3DRadSpace::Camera::SetLookDirection(const Quaternion& q)
{
	this->Rotation = q;
	this->lookat = Vector3::UnitZ() * q; //I hope that UnitZ is forward
}

void Engine3DRadSpace::Camera::SetLookDirection(const Vector3& v)
{
	this->lookat = v;
	//there's an infinite number of solutions that match the direction vector :pain:
	//how the heck I'm supposed to generate a quaternion from a direction vector??
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetViewMatrix() const
{
	return Engine3DRadSpace::Matrix::CreateLookAt(Position, lookat, Normal);
}

Engine3DRadSpace::Matrix Engine3DRadSpace::Camera::GetProjectionMatrix() const
{
	return Matrix::CreateProjectionFOV(this->FOV, 4.0f / 3.0f, this->NearPlaneDistance, this->FarPlaneDistance);
}

Engine3DRadSpace::Camera::~Camera()
{
}
