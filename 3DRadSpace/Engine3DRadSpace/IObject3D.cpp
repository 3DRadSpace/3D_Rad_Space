#include "IObject3D.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::IObject3D::IObject3D(const std::string &name, const std::string &tag, bool enabled, bool visible, const Math::Vector3 &pos, const Math::Vector3 &pivot,
	const Math::Quaternion &rotation, const Math::Vector3 &scale) :
	IObject(name, tag, enabled, visible)
{
}

Engine3DRadSpace::IObject3D::IObject3D(GraphicsDevice *device, const std::string &name, const std::string &tag, bool enabled, bool visible, const Math::Vector3 &pos, 
	const Math::Vector3 &pivot, const Math::Quaternion &rotation, const Math::Vector3 &scale) :
	IObject(device, name, tag, enabled, visible)
{
}

Engine3DRadSpace::Math::Matrix Engine3DRadSpace::IObject3D::GetModelMartix()
{
	return Matrix::CreateScale(Scale) * Matrix::CreateTranslation(-RotationCenter) * Matrix::CreateFromQuaternion(Rotation) * Matrix::CreateTranslation(Position);
}