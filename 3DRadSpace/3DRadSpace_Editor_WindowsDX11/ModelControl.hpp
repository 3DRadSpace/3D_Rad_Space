#pragma once
#include "AssetControl.hpp"
#include <Engine3DRadSpace/Reflection/Reflection.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class ModelControl : public AssetControl
{
	HWND _pictureBox = nullptr;
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

	Engine3DRadSpace::Reflection::RefModel3D ModelReference;

	void HandleClick(HWND clickedHandle) override;
};