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
	__stdstring Name;
	EditableFieldType Type;

	EditableField(__stdstring name, size_t n,EditableFieldType t) : Name(name), _value(new EditableFieldValue[n]),_size(n), Type(t) {};
	EditableField(const EditableField& field);

	EditableFieldValue& operator[](size_t i);
	size_t Size();

	~EditableField();
};