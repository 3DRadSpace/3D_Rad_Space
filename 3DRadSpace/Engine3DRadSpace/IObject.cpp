#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::IObject::IObject(GraphicsDevice *gdev, const std::string &name, const std::string &tag, bool enabled, bool visible, Vector3 pos, Vector3 rotCenter, Quaternion rot, Vector3 scale):
	_device(gdev),
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible),
	Position(pos),
	RotationCenter(rotCenter),
	Rotation(rot),
	Scale(scale)
{
}

IObject::IObject(const std::string &name,const std::string& tag, bool enabled, bool visible, Vector3 pos, Vector3 rotCenter, Quaternion rot, Vector3 scale):
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible),
	Position(pos),
	RotationCenter(rotCenter),
	Rotation(rot),
	Scale(scale)
{
}

Engine3DRadSpace::Math::Matrix Engine3DRadSpace::IObject::GetModelMartix()
{
	return Matrix::CreateScale(Scale) * Matrix::CreateTranslation(-RotationCenter) * Matrix::CreateFromQuaternion(Rotation) * Matrix::CreateTranslation(Position);
}

Engine3DRadSpace::GraphicsDevice *Engine3DRadSpace::IObject::GetGraphicsDeviceHandle()
{
	return _device;
}
