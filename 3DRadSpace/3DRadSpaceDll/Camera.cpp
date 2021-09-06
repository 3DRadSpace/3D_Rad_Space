#include "Camera.h"

Matrix Camera::GetTranslation()
{
	return Matrix::CreateTranslation(Position);
}

void Camera::Update(float dt)
{
	// we don't do anything here.
}

void Camera::Draw(float dt, Game* g)
{
	//we don't do anything here either
}

void Camera::Enable()
{
	this->Enabled = true;
}

char* Camera::WriteToFileBuffer(size_t& s)
{
	return nullptr;
}

IObject* Camera::ReadFromFileBuffer(char* fbuff, size_t s)
{
	return nullptr;
}

void Camera::SetLookDirection(const Quaternion& q)
{
	this->Rotation = q;
	this->lookat = Vector3::UnitZ() * q; //I hope that UnitZ is forward
}

void Camera::SetLookDirection(const Vector3& v)
{
	this->lookat = v;
	//there's an infinite number of solutions that match the direction vector :pain:
	//how the heck I'm supposed to generate a quaternion from a direction vector??
}

Matrix Camera::GetViewMatrix() const
{
	return Matrix::CreateLookAt(Position, lookat, Normal);
}

Matrix Camera::GetProjectionMatrix() const
{
	return Matrix::CreateProjectionFOV(this->FOV, 4.0f / 3.0f, this->NearPlaneDistance, this->FarPlaneDistance);
}

Camera::~Camera()
{
}
