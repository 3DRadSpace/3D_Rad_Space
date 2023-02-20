#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

IObject::IObject(std::string name, std::string tag, std::string resource, bool enabled, bool visible, Vector3 pos, Vector3 rotCenter, Quaternion rot, Vector3 scale):
	Name(name),
	Tag(tag),
	Resource(resource),
	Enabled(enabled),
	Visible(visible),
	Position(pos),
	RotationCenter(rotCenter),
	Rotation(rot),
	Scale(scale)
{
}