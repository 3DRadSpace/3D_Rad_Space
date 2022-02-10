#pragma once
#include "EditableFieldValue.hpp"

enum class EditableFieldType : uint8_t
{
	Undefined = 0,
	TextboxesOneLine,
	MultilineTextbox,
	NumericTextboxes,
	UpDowns,
	Color,
	Key,
	MultipleKeys
};

class EditableField
{
	EditableFieldValue* _value;
	size_t _size;
public:
	std::string Name;
	EditableFieldType Type;

	EditableField(std::string name, size_t n,EditableFieldType t) : Name(name), _value(new EditableFieldValue[n]),_size(n), Type(t) {};

	EditableFieldValue& operator[](size_t i);
	size_t Size();

	~EditableField();
};