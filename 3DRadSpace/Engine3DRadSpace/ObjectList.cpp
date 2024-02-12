#include "ObjectList.hpp"
#include "Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Internal;

Engine3DRadSpace::ObjectList::ObjectList(Game* owner):
	_game(owner)
{
}

unsigned ObjectList::Add(IObject* obj, InitializationFlag flag)
{
	bool internalInitialize = flag != InitializationFlag::NoInitialization;
	bool initialize = flag == InitializationFlag::Initialize || flag == InitializationFlag::InitializeAndLoad;
	bool load = flag == InitializationFlag::InitializeAndLoad || flag == InitializationFlag::Load;

	if (internalInitialize) obj->internalInitialize(_game);
	if (initialize) obj->Initialize();
	if (load) obj->Load(_game->Content.get());

	obj->internalInitialize(_game);
	obj->Initialize();
	obj->Load(_game->Content.get());

	std::shared_ptr<IObject> ptr;
	ptr.reset(obj);

	_objects.emplace_back(std::move(ptr));
	return unsigned(_objects.size() - 1);
}

unsigned ObjectList::Add(IObject2D* obj, InitializationFlag flag)
{
	return Add(static_cast<IObject*>(obj), flag);
}

unsigned ObjectList::Add(IObject3D* obj, InitializationFlag flag)
{
	return Add(static_cast<IObject*>(obj), flag);
}

IObject* ObjectList::Find(unsigned id)
{
	return _objects[id].Object.get();
}

IObject* ObjectList::Find(const std::string& name)
{
	for (auto& [object, id] : _objects)
	{
		if (object->Name == name)
			return object.get();
	}
	return nullptr;
}

void ObjectList::Remove(unsigned id)
{
	_objects.erase(_objects.begin() + id, _objects.begin() + id + 1);
}

void ObjectList::Remove(const std::string& name)
{
	std::erase_if(_objects, [name](ObjectInstance& p) -> bool
		{
			return p.Object->Name == name;
		});
}

void ObjectList::Remove(IObject* obj)
{
	std::erase_if(_objects, [obj](ObjectInstance& p) -> bool
		{
			return p.Object.get() == obj;
		});
}

void ObjectList::RemoveIf(std::function<bool(IObject*)> f)
{
	std::erase_if(_objects, [f](ObjectInstance& p) -> bool
		{
			return f(p.Object.get());
		});
}

void ObjectList::Replace(IObject* obj, unsigned id)
{
	_objects[id].Object.reset(obj);
}

void ObjectList::Clear()
{
	_objects.clear();
}

IObject* Engine3DRadSpace::ObjectList::operator[](unsigned i) const
{
	return _objects[i].Object.get();
}

size_t Engine3DRadSpace::ObjectList::Count() const noexcept
{
	return _objects.size();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::begin()
{
	return _objects.begin();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::end()
{
	return _objects.end();
}

template<>
ObjectList::ObjectInstance::ObjectInstance(std::shared_ptr<IObject>&& obj) : 
	Object(std::move(obj))
{
	auto ptr = Object.get();

	InternalType = ObjectType::IObject;
	if (dynamic_cast<IObject2D*>(ptr) != nullptr) InternalType = ObjectType::IObject2D;
	else if (dynamic_cast<IObject3D*>(ptr) != nullptr)  InternalType = ObjectType::IObject3D;
}
