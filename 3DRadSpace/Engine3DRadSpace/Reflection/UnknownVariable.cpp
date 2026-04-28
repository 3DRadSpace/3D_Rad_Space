#include "UnknownVariable.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

UnknownVariable::UnknownVariable(
	size_t offset,
	size_t size,
	const std::string& name,
	const std::string& desc
) : IReflectedField(offset, size, name, desc, typeid(void))
{
}

const void* UnknownVariable::Get(void* objPtr) const
{
	(void)objPtr;
	return nullptr;
}

void UnknownVariable::Set(void* objPtr, const void* value) const
{
	(void)objPtr;
	(void)value;
}

const void* UnknownVariable::DefaultValue() const
{
	return nullptr;
}

FieldRepresentation UnknownVariable::Representation() const
{
	return { {FieldRepresentationType::None, ""} };
}

std::unique_ptr<IReflectedField> UnknownVariable::Clone() const
{
	return std::make_unique<UnknownVariable>(*this);
}