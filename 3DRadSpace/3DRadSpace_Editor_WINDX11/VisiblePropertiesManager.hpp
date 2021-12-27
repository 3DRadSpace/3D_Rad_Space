#pragma once
#include "Libs.hpp"

enum class EditableFieldType : int8_t
{
	Undefined,
	String,
	BooleanValue,
	NaturalNumber,
	RealNumber,
	Vector2D,
	Vector3D,
	ColorRGB,
	ColorRGBA,
	File,
	SourceCode,
	EventList,
	CustomImplementation,
};

struct EditableField
{
	EditableField(const EditableFieldType t,const __rawstring* n) : Type(t), Name(n) {};
	const EditableFieldType Type;
	const __rawstring* Name;
};

class VisiblePropertiesManager
{
	std::vector<EditableField> EditableFields;
public:
	VisiblePropertiesManager(EditableField* ef, size_t numEf, std::function<HWND*(HWND,HINSTANCE)>);

	EditableField& operator[](size_t i);

	size_t Size() const;

	size_t GetControlsNum() const;
};

