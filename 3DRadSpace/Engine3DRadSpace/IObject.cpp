#include "IObject.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

IObject::IObject(Game* game, const std::string& name, const std::string& tag, bool enabled, bool visible) :
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible),
	_game(game),
	_device(game->Device.get())
{
}

IObject::IObject(const std::string &name,const std::string& tag, bool enabled, bool visible) :
	Name(name),
	Tag(tag),
	Enabled(enabled),
	Visible(visible)
{
}

GraphicsDevice* IObject::GetGraphicsDeviceHandle()
{
	return _device;
}

Game* IObject::GetGame()
{
	return _game;
}
