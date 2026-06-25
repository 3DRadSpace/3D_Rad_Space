#include "IObject.hpp"
#include "ObjectList.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

IObject::IObject(const std::string& name, bool enabled, bool visible) :
	_parent(nullptr),
	Name(name),
	Enabled(enabled),
	Visible(visible),
	Children(this)
{
}

void IObject::InternalInitialize(IGame* game)
{
	_game = game;
	_device = game->GetService<IGraphicsDevice>({});
}

IGraphicsDevice* IObject::GetGraphicsDeviceHandle() const noexcept
{
	return _device;
}

IGame* IObject::GetGame() const noexcept
{
	return _game;
}

void IObject::Enable()
{
	Enabled = true;
}

void IObject::Disable()
{
	Enabled = false;
}

bool IObject::Switch()
{
	Enabled = !Enabled;
	return Enabled;
}

void IObject::Show()
{
	Visible = true;
}

void IObject::Hide()
{
	Visible = false;
}

bool IObject::SwitchVisibility()
{
	Visible = !Visible;
	return Visible;
}

IObject* IObject::operator[](size_t idxChild) const
{
	return Children[idxChild];
}

IObject* IObject::GetParent() const noexcept
{
	return _parent;
}

void IObject::SetParent(IObject* newParent) noexcept
{
	auto oldParent = _parent;
	_parent = newParent;
	newParent->Children._objects.push_back(this);

	if(oldParent != nullptr) 
	{
		oldParent->Children.Remove(this);
		oldParent = nullptr;
	}
}

bool IObject::HasParent() const noexcept
{
	return _parent != nullptr;
}

size_t IObject::GetChildrenCount() const noexcept
{
	return Children.Count();
}

IObject::~IObject()
{
}