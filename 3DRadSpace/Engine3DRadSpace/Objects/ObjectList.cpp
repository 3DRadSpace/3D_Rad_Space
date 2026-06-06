#include "ObjectList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Internal;

ObjectList::ObjectList(IGame* owner) : IService(owner),
	_camera(nullptr)
{
}


void ObjectList::_validate(ObjectInstance& instance)
{
	instance.Object->InternalInitialize(_owner);
	
	if (_owner->WasInitialized())
	{
		instance.Object->Initialize();
	}

	if (_owner->WasLoaded())
	{
		instance.Object->Load();
	}
}

void ObjectList::_validate(IObject* instance)
{
	if (_owner->WasInitialized())
	{
		instance->InternalInitialize(_owner);
		instance->Initialize();
	}

	if (_owner->WasLoaded())
	{
		instance->Load();
	}
}


unsigned ObjectList::Add(IObject* obj)
{
	obj->InternalInitialize(_owner);

	std::unique_ptr<IObject> ptr;
	ptr.reset(obj);

	auto& added_obj = _objects.emplace_back(std::move(ptr));

	_validate(added_obj);

	return unsigned(_objects.size() - 1);
}

IObject* ObjectList::Find(const std::string& name) const noexcept
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

void ObjectList::Replace(IObject* obj, unsigned id) noexcept
{
	auto context = static_cast<IGame*>(_objects[id].Object->GetGame());
	_objects[id].Object.reset(obj);

	_objects[id].Object->InternalInitialize(context);

	if(context->WasInitialized())
		_objects[id].Object->Initialize();

	if(context->WasLoaded())
		_objects[id].Object->Load();
}

void ObjectList::Clear() noexcept
{
	_objects.clear();
}

IObject* ObjectList::operator[](size_t i) const
{
	return _objects[i].Object.get();
}

size_t ObjectList::Count() const noexcept
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

std::vector<ObjectList::ObjectInstance>::const_iterator ObjectList::begin() const
{
	return _objects.begin();
}

std::vector<ObjectList::ObjectInstance>::const_iterator ObjectList::end() const
{
	return _objects.end();
}

template<>
ObjectList::ObjectInstance::ObjectInstance(std::unique_ptr<IObject>&& obj) : 
	Object(std::move(obj))
{
	auto ptr = Object.get();

	InternalType = ObjectType::IObject;
	if (dynamic_cast<IObject2D*>(ptr) != nullptr) InternalType = ObjectType::IObject2D;
	else if (dynamic_cast<IObject3D*>(ptr) != nullptr)  InternalType = ObjectType::IObject3D;
}

ObjectList::ObjectInstance::ObjectInstance(IObject* obj)
{
	Object.reset(obj);

	auto ptr = Object.get();

	InternalType = ObjectType::IObject;
	if (dynamic_cast<IObject2D*>(ptr) != nullptr) InternalType = ObjectType::IObject2D;
	else if (dynamic_cast<IObject3D*>(ptr) != nullptr)  InternalType = ObjectType::IObject3D;
}

IObject* ObjectList::ObjectInstance::operator->() const noexcept
{
	return Object.get();
}

ICamera* ObjectList::GetRenderingCamera() const noexcept
{
	return _camera;
}

void ObjectList::SetRenderingCamera(ICamera* cam) noexcept
{
	_camera = cam;
}