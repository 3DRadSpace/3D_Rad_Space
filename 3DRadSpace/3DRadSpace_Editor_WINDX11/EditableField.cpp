#include "EditableField.hpp"

EditableField::EditableField(const EditableField& field) :
	Name(TEXT("")),
	_value(new EditableFieldValue[field._size]),
	_size(field._size), Type(field.Type)
{
	Name += field.Name;
	std::copy(field._value, field._value + field._size, _value);
}

EditableFieldValue& EditableField::operator[](size_t i)
{
	return _value[i];
}

size_t EditableField::Size()
{
	return this->_size;
}

EditableField::~EditableField()
{
	if(_value != nullptr) delete[] _value;
	_value = nullptr;
}