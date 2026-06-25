#include "ObjectCollection.hpp"
#include "IObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

ChildObjectCollection::ChildObjectCollection(IObject* owner) : _owner(owner)
{
}

void ChildObjectCollection::Add(IObject* ptr)
{
	if(ptr == nullptr) return;

	ptr->SetParent(_owner);
	_objects.push_back(ptr);
}

void ChildObjectCollection::Remove(IObject* ptr)
{
	if(ptr == nullptr) return;

	ptr->SetParent(nullptr);

	if (!_objects.empty())
	{
		_objects.erase(std::remove(_objects.begin(), _objects.end(), ptr), _objects.end());
	}
}

void ChildObjectCollection::Remove(size_t index)
{
	if (index >= _objects.size()) return;

	_objects.at(index)->SetParent(nullptr);
	_objects.erase(_objects.begin() + index);
}

IObject* ChildObjectCollection::operator[](size_t index) const
{
	if(index > _objects.size()) return nullptr;
	return _objects.at(index);
}

IObject*& ChildObjectCollection::operator[](size_t index)
{
	return _objects.at(index);
}

size_t ChildObjectCollection::Count() const noexcept
{
	return _objects.size();
}

void ChildObjectCollection::Clear()
{
	auto detachedList = std::move(_objects);

	for (auto& obj : detachedList)
	{
		if(obj) obj->SetParent(nullptr);
	}
}

std::vector<IObject*> ChildObjectCollection::Find(std::function<bool(IObject*)> predicate) const noexcept
{
	std::vector<IObject*> r;

	for(const auto& obj : _objects) 
		if(predicate(obj)) r.push_back(obj);

	return r;
}

std::vector<IObject*>::iterator ChildObjectCollection::begin() noexcept
{
	return _objects.begin();
}

std::vector<IObject*>::const_iterator ChildObjectCollection::begin() const noexcept
{
	return _objects.begin();
}

std::vector<IObject*>::iterator ChildObjectCollection::end() noexcept
{
	return _objects.end();
}

std::vector<IObject*>::const_iterator ChildObjectCollection::end() const noexcept
{
	return _objects.cend();
}