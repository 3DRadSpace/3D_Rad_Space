#include "ShaderVariable.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Reflection;

ShaderVariable::ShaderVariable(
	const std::string& name,
	int idxCbuffer,
	size_t offset,
	size_t size
) : IReflectedField(offset, size, name, "", typeid(void)),
	_idxCbuffer(idxCbuffer)
{
}

const void* ShaderVariable::Get(void* objPtr) const
{
	return static_cast<std::byte*>(objPtr) + _offset;
}

void ShaderVariable::Set(void* objPtr, const void* value) const
{
	assert(objPtr != nullptr);
	assert(value != nullptr);

	memcpy_s(
		static_cast<std::byte*>(objPtr) + _offset,
		_size,
		value,
		_size
	);
}

const void* ShaderVariable::DefaultValue() const
{
	return nullptr;
}

FieldRepresentation ShaderVariable::Representation() const
{
	return { { FieldRepresentationType::None, "" } };
}

int ShaderVariable::ConstantBuffer() const noexcept
{
	return _idxCbuffer;
}

std::unique_ptr<IReflectedField> ShaderVariable::Clone() const
{
	return std::make_unique<ShaderVariable>(*this);
}