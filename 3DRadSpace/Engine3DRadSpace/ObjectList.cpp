#include "ObjectList.hpp"

using namespace Engine3DRadSpace;

unsigned ObjectList::Add(IObject* obj)
{
	std::shared_ptr<IObject> ptr;
	ptr.reset(obj);

	objects.emplace_back(std::move(ptr));
	return unsigned(objects.size() - 1);
}

unsigned ObjectList::Add(IObject2D* obj)
{
	return Add(static_cast<IObject*>(obj));
}

unsigned ObjectList::Add(IObject3D* obj)
{
	return Add(static_cast<IObject*>(obj));
}

IObject* ObjectList::Find(unsigned id)
{
	return objects[id].Object.get();
}

IObject* ObjectList::Find(const std::string& name)
{
	for (auto& [object, id] : objects)
	{
		if (object->Name == name)
			return object.get();
	}
	return nullptr;
}

void ObjectList::Remove(unsigned id)
{
	objects.erase(objects.begin() + id, objects.begin() + id + 1);
}

void ObjectList::Remove(const std::string& name)
{
	std::erase_if(objects, [name](ObjectInstance& p) -> bool
		{
			return p.Object->Name == name;
		});
}

void ObjectList::Remove(IObject* obj)
{
	std::erase_if(objects, [obj](ObjectInstance& p) -> bool
		{
			return p.Object.get() == obj;
		});
}

void ObjectList::RemoveIf(std::function<bool(IObject*)> f)
{
	std::erase_if(objects, [f](ObjectInstance& p) -> bool
		{
			return f(p.Object.get());
		});
}

void ObjectList::Replace(IObject* obj, unsigned id)
{
	objects[id].Object.reset(obj);
}

void ObjectList::Clear()
{
	objects.clear();
}

IObject* Engine3DRadSpace::ObjectList::operator[](unsigned i) const
{
	return objects[i].Object.get();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::begin()
{
	return objects.begin();
}

std::vector<ObjectList::ObjectInstance>::iterator ObjectList::end()
{
	return objects.end();
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
