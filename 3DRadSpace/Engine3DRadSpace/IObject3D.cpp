#include "IObject3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

IObject3D::IObject3D(const std::string &name, const std::string &tag, bool enabled, bool visible, const Vector3&pos, const
                     Vector3&pivot,
                     const Quaternion&rotation, const Vector3&scale) :
	IObject(name, tag, enabled, visible)
{
}

IObject3D::IObject3D(Game *game, const std::string &name, const std::string &tag, bool enabled, bool visible, const
                     Vector3&pos, 
                     const Vector3&pivot, const Quaternion&rotation, const Vector3&scale) :
	IObject(game, name, tag, enabled, visible)
{
}

Matrix4x4 IObject3D::GetModelMartix()
{
	return Matrix4x4::CreateScale(Scale) * Matrix4x4::CreateTranslation(-RotationCenter) * Matrix4x4::CreateFromQuaternion(Rotation) * Matrix4x4::CreateTranslation(Position);
}