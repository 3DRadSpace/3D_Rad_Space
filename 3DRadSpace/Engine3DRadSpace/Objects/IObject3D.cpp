#include "IObject3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject3D::IObject3D(const std::string &name, bool enabled, bool visible, const Vector3&pos, const Vector3&pivot,
					 const Quaternion& rotation, const Vector3& scale) :
	IObject(name, enabled, visible),
	Position(pos),
	RotationCenter(pivot),
	Rotation(rotation),
	Scale(scale)
{
}

Matrix4x4 IObject3D::GetLocalMatrix() const
{
	return  Matrix4x4::CreateScale(Scale)*
			Matrix4x4::CreateTranslation(-RotationCenter)*
			Matrix4x4::CreateFromQuaternion(Rotation)*
			Matrix4x4::CreateTranslation(RotationCenter)*
			Matrix4x4::CreateTranslation(Position);
}

Matrix4x4 IObject3D::GetModelMatrix() const
{
	Matrix4x4 local = GetLocalMatrix();

	if (_parent == nullptr)
		return local;

	auto parent3D = dynamic_cast<IObject3D*>(_parent);
	if (parent3D)
		return local * parent3D->GetModelMatrix();
	else
		return local;
}

BoundingBox IObject3D::GetBoundingBox() const noexcept
{
	return BoundingBox(Position, Vector3(0, 0, 0));
}