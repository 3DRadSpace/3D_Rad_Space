#include "EditableField.hpp"

EditableFieldValue& EditableField::operator[](size_t i)
{
	return _value[i];
}

EditableField::~EditableField()
{
	if(_value != nullptr) delete[] _value;
	_value = nullptr;
}