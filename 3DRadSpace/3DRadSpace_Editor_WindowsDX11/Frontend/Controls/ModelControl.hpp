#pragma once
#include "AssetControl.hpp"
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class SkinmeshPreviewer;
class ModelControl : public AssetControl
{
	HWND _pictureBox = nullptr;
	HWND _previewButton = nullptr;
	HBITMAP _image = nullptr;
	std::unique_ptr<SkinmeshPreviewer> _previwer = nullptr;
public:
	ModelControl(
		HWND owner,
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		unsigned model,
		const std::string& name,
		int x,
		int y
	);

	ModelControl(ModelControl&) = delete;
	ModelControl& operator=(ModelControl&) = delete;

	ModelControl(ModelControl&&) = default;
	ModelControl& operator=(ModelControl&&) = default;

	HWND GetPictureBox();

	void HandleClick(HWND clickedHandle) override;

	~ModelControl() override;
};