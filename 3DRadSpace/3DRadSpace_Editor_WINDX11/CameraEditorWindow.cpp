#include "CameraEditorWindow.hpp"

Engine3DRadSpace::IObject* CameraEditorWindow::CreateObject(EditableFieldCollection* editableFields)
{
	return new Engine3DRadSpace::Camera(nullptr, editableFields->ObjectName, true, //object name + default state
		Engine3DRadSpace::Vector3(std::get<float>(editableFields[0][0][0].Value), std::get<float>(editableFields[0][0][1].Value), std::get<float>(editableFields[0][0][2].Value)), //position
		Engine3DRadSpace::Quaternion::CreateFromYawPitchRoll(std::get<float>(editableFields[0][1][1].Value), std::get<float>(editableFields[0][1][0].Value), std::get<float>(editableFields[0][1][2].Value)), //rotation
		Engine3DRadSpace::Vector3(std::get<float>(editableFields[0][2][0].Value), std::get<float>(editableFields[0][2][1].Value), std::get<float>(editableFields[0][2][2].Value)), //normal character vector
		std::get<float>(editableFields[0][3][0].Value), //field of view
		std::get<float>(editableFields[0][3][1].Value), //aspect ratio
		std::get<float>(editableFields[0][3][2].Value), //near plane distance
		std::get<float>(editableFields[0][3][3].Value)); //far plane distance
}

/*
std::vector<std::variant<__stdstring, float>> CameraEditorWindow::SetEditorWindowValues(Engine3DRadSpace::IObject* obj)
{
	return { 0.0f,0.0f,0.0f, //position
			0.0f,0.0f,0.0f, //rotation (euler angles)
			0.0f,0.0f,0.0f, //normal vector rotation
			65.0f, //field of view
			800.0f / 600.0f, //aspect ratio
			0.01f, //near plane distance
			500.0f //far plane distance
	};
}

std::vector<std::variant<__stdstring, float>> CameraEditorWindow::SetEditorWindowDefaultValues()
{
	return { TEXT("Camera"),0.0f,0.0f,0.0f, //position
	0.0f,0.0f,0.0f };
}

std::vector<__stdstring> CameraEditorWindow::GetEditorWindowTitles()
{
	return { TEXT("Camera"), TEXT("Position"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Rotation"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Normal"), TEXT("X"), TEXT("Y"), TEXT("Z"),
			TEXT("Camera specific settings"), TEXT("FOV"), TEXT("Aspect ratio"), TEXT("Near plane distance"), TEXT("Far plane distance") };
}
*/

const __rawstring CameraEditorWindow::GetHelpURL()
{
	return TEXT("http:\\3dradspace.com\\Documentation");
}

const char* CameraEditorWindow::GetObjectName()
{
	return "Camera";
}

EditableFieldCollection CameraEditorWindow::GetFields()
{
	std::vector<EditableField> v = std::vector<EditableField>(
	{
		{TEXT("Position"),3,EditableFieldType::NumericTextboxes},
		{TEXT("Rotation"),3,EditableFieldType::NumericTextboxes},
		{TEXT("Normal"),3,EditableFieldType::NumericTextboxes},
		{TEXT("Camera specific settings"),4,EditableFieldType::UpDowns}
	});
	EditableFieldCollection c = EditableFieldCollection(v);
	for(size_t i = 0; i < 3; i++)
	{
		c[i][0] = { TEXT("X"),TEXT("0") };
		c[i][1] = { TEXT("Y"),TEXT("0") };
		c[i][2] = { TEXT("Z"),TEXT("0") };
	}
	return c;
}