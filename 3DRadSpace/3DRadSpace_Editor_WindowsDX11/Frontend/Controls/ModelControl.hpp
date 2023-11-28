#pragma once
#include "AssetControl.hpp"
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class ModelControl : public AssetControl
{
	HWND _pictureBox = nullptr;
	HWND _previewButton = nullptr;
	HBITMAP _image = nullptr;
public:
	ModelControl(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		Engine3DRadSpace::Reflection::RefModel3D model,
		const std::string& name,
		int x,
		int y
	);

	ModelControl(ModelControl&) = delete;
	ModelControl& operator=(ModelControl&) = delete;

	ModelControl(ModelControl&&) = default;
	ModelControl& operator=(ModelControl&&) = default;

	HWND GetPictureBox();

	Engine3DRadSpace::Reflection::RefModel3D ModelReference;

	void HandleClick(HWND clickedHandle) override;

	~ModelControl() override;
};