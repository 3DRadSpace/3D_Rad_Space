#include "Attribute.hpp"	

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

Attribute::Attribute(const std::string& name, const std::string& value) : IReflectedField(0, 0, name, value, typeid(void))
{
}

const void* Attribute::Get(void* objPtr) const
{
	(void)objPtr;
	return nullptr;
}

void Attribute::Set(void* objPtr, const void* value) const
{
	(void)objPtr;
	(void)value;
}

const void* Attribute::DefaultValue() const
{
	return nullptr;
}

FieldRepresentation Attribute::Representation() const
{
	return FieldRepresentation{{FieldRepresentationType::None, ""}};
}

std::unique_ptr<IReflectedField> Attribute::Clone() const
{
	return std::make_unique<Attribute>(FieldName(), FieldDesc());
}