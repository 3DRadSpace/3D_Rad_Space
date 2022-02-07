#include "EditableFieldCollection.hpp"

EditableFieldCollection::EditableFieldCollection(std::vector<EditableField>& fields) : 
	_fields(static_cast<EditableField*>(::operator new[](sizeof(EditableField)* fields.size()))), _size(fields.size())
{
	std::copy(fields.begin(), fields.end(), this->_fields);
}

size_t EditableFieldCollection::Size()
{
	return this->_size;
}

size_t EditableFieldCollection::CountCreatedElements()
{
	size_t c = 0;
	for(size_t i = 0; i < this->_size; i++)
	{
		c += this->_fields[i].Size();
	}
	return c;
}

EditableField& EditableFieldCollection::operator[](size_t i)
{
	return this->_fields[i];
}

EditableFieldCollection::~EditableFieldCollection()
{
	if(this->_fields != nullptr) delete[] this->_fields;
	this->_fields = nullptr;
}