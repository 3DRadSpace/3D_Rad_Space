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

Matrix IObject3D::GetModelMartix()
{
	return Matrix::CreateScale(Scale) * Matrix::CreateTranslation(-RotationCenter) * Matrix::CreateFromQuaternion(Rotation) * Matrix::CreateTranslation(Position);
}