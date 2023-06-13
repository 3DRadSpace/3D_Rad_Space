#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::IObject::IObject(GraphicsDevice *gdev, const std::string &name, const std::string &tag, bool enabled, bool visible) :
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible)
{
}

IObject::IObject(const std::string &name,const std::string& tag, bool enabled, bool visible) :
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible)
{
}

Engine3DRadSpace::GraphicsDevice *Engine3DRadSpace::IObject::GetGraphicsDeviceHandle()
{
	return _device;
}
