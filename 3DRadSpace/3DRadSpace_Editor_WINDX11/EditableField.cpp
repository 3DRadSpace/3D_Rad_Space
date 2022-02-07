#include "EditableField.hpp"

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