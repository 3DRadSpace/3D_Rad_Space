#pragma once
#include "EditableFieldValue.hpp"

class EditableField
{
	EditableFieldValue* _value;
	size_t _size;
public:
	std::string Name;

	EditableField(std::string name, size_t n) : Name(name), _value(new EditableFieldValue[n]),_size(n) {};

	EditableFieldValue& operator[](size_t i);

	~EditableField();
};