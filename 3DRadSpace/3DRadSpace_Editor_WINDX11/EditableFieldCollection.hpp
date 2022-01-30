#pragma once
#include "EditableField.hpp"

class EditableFieldCollection
{
	EditableField* _fields;
	size_t _size;
public:
	EditableFieldCollection(std::vector<EditableField>& fields);

	size_t Size();
	size_t CountCreatedElements();

	EditableField& operator[](size_t i);

	~EditableFieldCollection();
};