#include "IObject.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;

Engine3DRadSpace::IObject::IObject(Game* game, const std::string& name, const std::string& tag, bool enabled, bool visible) :
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

Engine3DRadSpace::GraphicsDevice *Engine3DRadSpace::IObject::GetGraphicsDeviceHandle()
{
	return _device;
}

Game* Engine3DRadSpace::IObject::GetGame()
{
	return _game;
}
