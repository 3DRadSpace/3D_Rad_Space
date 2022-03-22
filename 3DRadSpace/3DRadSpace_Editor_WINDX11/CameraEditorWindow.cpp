#include "CameraEditorWindow.hpp"

__stdstring CameraEditorWindow::_gFieldNames[] = {TEXT("Position"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Rotation"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Normal"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Camera specific settings"), TEXT("FOV"), TEXT("Aspect ratio"), TEXT("Near plane distance"), TEXT("Far plane distance") };

__stdstring CameraEditorWindow::_gFieldValues[] = {
	TEXT("0"),TEXT("0"),TEXT("0"), //pos
	TEXT("0"),TEXT("0"),TEXT("0"), //rot
	TEXT("0"),TEXT("1"),TEXT("0"), //norm
	TEXT("65"),TEXT("0"),TEXT("0.001"),TEXT("500"), //fov, aspect ratio, npd, fpd
};

Engine3DRadSpace::IObject* CameraEditorWindow::CreateObject(std::vector<__stdstring> &fieldValues)
{
	return new Engine3DRadSpace::Camera(nullptr, this->GetObjectName(), true, //object name + default state
		Engine3DRadSpace::Vector3(std::stof(fieldValues[0]), std::stof(fieldValues[1]), std::stof(fieldValues[2])), //position
		Engine3DRadSpace::Quaternion::CreateFromYawPitchRoll(std::stof(fieldValues[4]), std::stof(fieldValues[3]), std::stof(fieldValues[5])), //rotation (y,x,z / yaw-pitch-roll)
		Engine3DRadSpace::Vector3(std::stof(fieldValues[6]), std::stof(fieldValues[7]), std::stof(fieldValues[8])), //normal character vector
		std::stof(fieldValues[9]), //field of view
		std::stof(fieldValues[10]), //aspect ratio
		std::stof(fieldValues[11]), //near plane distance
		std::stof(fieldValues[12])); //far plane distance
}

const __rawstring CameraEditorWindow::GetHelpURL()
{
	return TEXT("http:\\3dradspace.com\\Documentation");
}

const char* CameraEditorWindow::GetObjectName()
{
	return "Camera";
}

__stdstring* CameraEditorWindow::GetFieldNames()
{
	return this->_gFieldNames;
}

size_t CameraEditorWindow::GetFieldNamesCount()
{
	return sizeof(this->_gFieldNames) / sizeof(__stdstring*);
}

__stdstring* CameraEditorWindow::GetFieldValues()
{
	return _gFieldValues;
}

size_t CameraEditorWindow::GetFieldValuesCount()
{
	return sizeof(this->_gFieldNames) / sizeof(__stdstring*);
}

std::vector<EditableFieldType> CameraEditorWindow::GetFieldFormTypes()
{
	return { 
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,

		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,

		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,

		EditableFieldType::UpDowns,
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,
		EditableFieldType::TextboxesOneLine,
	};
}