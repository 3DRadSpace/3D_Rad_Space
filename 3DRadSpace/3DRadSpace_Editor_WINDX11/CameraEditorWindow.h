#pragma once
#include "IObjectEditorWindow.hpp"
class CameraEditorWindow : public IObjectEditorWindow
{
public:
	Engine3DRadSpace::IObject* CreateObject(EditableFieldCollection* editableFields) override
	{
		return new Engine3DRadSpace::Camera(nullptr, editableFields->ObjectName, editableFields->Enabled, //object name + default state
			Engine3DRadSpace::Vector3(std::get<float>(editableFields[0][0][0].Value), std::get<float>(editableFields[0][0][1].Value), std::get<float>(editableFields[0][0][2].Value)), //position
			Engine3DRadSpace::Quaternion::CreateFromYawPitchRoll(std::get<float>(editableFields[0][1][1].Value), std::get<float>(editableFields[0][1][0].Value), std::get<float>(editableFields[0][1][2].Value)), //rotation
			Engine3DRadSpace::Vector3(std::get<float>(editableFields[0][2][0].Value), std::get<float>(editableFields[0][2][1].Value), std::get<float>(editableFields[0][2][2].Value)), //normal character vector
			std::get<float>(editableFields[0][3][0].Value), //field of view
			std::get<float>(editableFields[0][3][1].Value), //aspect ratio
			std::get<float>(editableFields[0][3][2].Value), //near plane distance
			std::get<float>(editableFields[0][3][3].Value)); //far plane distance
	}
	virtual std::vector<std::variant<__stdstring, float>> SetEditorWindowValues(Engine3DRadSpace::IObject* obj) override
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
	virtual std::vector<std::variant<__stdstring, float>> SetEditorWindowDefaultValues() override
	{
		return {TEXT("Camera"),0.0f,0.0f,0.0f, //position
		0.0f,0.0f,0.0f };
	}
	virtual std::vector<__stdstring> GetEditorWindowTitles() override
	{
		return { TEXT("Camera"),TEXT("Position"),TEXT("X"),TEXT("Y"),TEXT("Z"),
				TEXT("Rotation"),TEXT("X"),TEXT("Y"),TEXT("Z"), 
				TEXT("Normal"),TEXT("X"),TEXT("Y"),TEXT("Z"),
				TEXT("Camera specific settings"), TEXT("FOV"),TEXT("Aspect ratio"),TEXT("Near plane distance"),TEXT("Far plane distance")};
	}
	virtual __stdstring GetHelpURL() override
	{
		return TEXT("http:\\3dradspace.com\\Documentation");
	}
};

