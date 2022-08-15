#include "IObjectReflection.hpp"

Engine3DRadSpace::Reflection::ReflectedFieldBase::~ReflectedFieldBase()
{
}

Engine3DRadSpace::Reflection::Reflect::Reflect(const std::initializer_list<std::function<ReflectedFieldBase* ()>> fields) :
	_numFields(fields.size()),
	_fields(fields.size())
{
	for(size_t i = 0; i < this->_numFields; i++)
	{
		_fields[i] = (*(fields.begin() + i))();
	}
}
const size_t Engine3DRadSpace::Reflection::Reflect::Size() const
{
	return this->_numFields;
}

const Engine3DRadSpace::Reflection::ReflectedFieldBase* Engine3DRadSpace::Reflection::Reflect::operator[](size_t index) const
{
	return this->_fields[index];
}
