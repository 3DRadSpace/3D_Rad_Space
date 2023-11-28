#include "IObject.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

IObject::IObject(const std::string &name,const std::string& tag, bool enabled, bool visible) :
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible)
{
}

void Engine3DRadSpace::IObject::internalInitialize(Game* game)
{
	_game = game;
}

GraphicsDevice* IObject::GetGraphicsDeviceHandle()
{
	return _device;
}

Game* IObject::GetGame()
{
	return _game;
}
