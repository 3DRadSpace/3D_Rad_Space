#include "ReflectedObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;

ReflectedObject::ReflectedObject(
	const std::string& name,
	const std::string& category,
	const std::string& desc,
	const std::span<IReflectedField*> obj_fields,
	const UUID& uuid
) :
	Name(name),
	_fields(obj_fields.begin(), obj_fields.end()),
	Category(category),
	Description(desc),
	ObjectUUID(uuid)
{
	CreateBlankObject = []()
	{
		return nullptr;
	};
}

size_t ReflectedObject::NumFields() const noexcept
{
    return _fields.size()  - 1;
}

const IReflectedField* ReflectedObject::operator[](unsigned i)
{
    return _fields[i];
}

const IReflectedField* ReflectedObject::operator[](const std::string& name)
{
	//First find attempt: check if field name and name exactly match. O(#fields)
	for (auto& field : _fields)
	{
		if (field->FieldName() == name) return field;
	}

	return nullptr;
}

std::vector<IReflectedField *>::iterator ReflectedObject::begin()
{
	return _fields.begin();
}

std::vector<IReflectedField *>::iterator ReflectedObject::end()
{
	return std::prev(_fields.end()); //do not return the last element, it is a ReflectedField<void>.
}

std::unique_ptr<ReflectedObject> ReflectedObject::Clone() const
{
	std::vector<IReflectedField*> clonedFields;
	for (auto& field : _fields)
	{
		clonedFields.push_back(field->Clone().release());
	}
	return std::make_unique<ReflectedObject>(Name, Category, Description, clonedFields, ObjectUUID);
}

ReflectedObject::~ReflectedObject()
{
	for (auto& field : *this)
	{
		delete field;
	}
}