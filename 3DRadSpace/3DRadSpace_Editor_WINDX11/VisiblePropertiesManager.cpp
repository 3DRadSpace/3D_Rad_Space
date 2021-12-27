#include "VisiblePropertiesManager.hpp"

VisiblePropertiesManager::VisiblePropertiesManager(EditableField* ef, size_t numEf, std::function<HWND* (HWND, HINSTANCE)>)
{
	for(size_t i = 0; i < numEf; i++)
	{
		EditableFields.push_back(ef[i]);
	}
}

EditableField& VisiblePropertiesManager::operator[](size_t i)
{
	return this->EditableFields[i];
}

size_t VisiblePropertiesManager::Size() const
{
	return this->EditableFields.size();
}

size_t VisiblePropertiesManager::GetControlsNum() const 
{
	size_t sum = 0;
	for(size_t i = 0; i < EditableFields.size(); i++)
	{
		switch(EditableFields[i].Type)
		{
			case EditableFieldType::String: //static control + edit
			case EditableFieldType::BooleanValue: //static control + checkbox
			case EditableFieldType::NaturalNumber: //static control + updown control
			case EditableFieldType::RealNumber: //static control + edit
			case EditableFieldType::SourceCode: //groupbox + edit
			case EditableFieldType::EventList: //listbox + groupbox
				sum += 2;
				break;
			case EditableFieldType::Vector2D: // 2 edit controls + 1 group box
			case EditableFieldType::File: // 1 groupbox, 1 button , 1 edit control
				sum += 3;
				break;
			case EditableFieldType::ColorRGB: //3 edit controls, 1 groupbox
			case EditableFieldType::Vector3D: //3 edit controls, 1 groupbox
				sum += 4;
				break;
			case EditableFieldType::ColorRGBA: //4 edit controls, 1 groupbox
				sum += 5;
				break;
		}
	}
	return sum;
}
