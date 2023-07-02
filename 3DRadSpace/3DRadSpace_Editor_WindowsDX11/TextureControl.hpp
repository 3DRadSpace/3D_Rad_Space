#pragma once
#include "AssetControl.hpp"
#include <Engine3DRadSpace/Reflection/ReflectedField.hpp>
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class TextureControl : public AssetControl
{
	HWND _pictureBox;
	HBITMAP _image;
public:
	TextureControl(
		HWND owner, 
		HINSTANCE hInstance,
		Engine3DRadSpace::Content::ContentManager* content,
		Engine3DRadSpace::Reflection::RefTexture2D texture, 
		const std::string &name, 
		int x,
		int y
	);

	TextureControl(TextureControl &) = delete;
	TextureControl &operator=(TextureControl &) = delete;

	TextureControl(TextureControl &&c) noexcept;
	TextureControl &operator=(TextureControl &&c) noexcept;

	Engine3DRadSpace::Reflection::RefTexture2D TextureReference;

	HWND GetPixturebox();

	~TextureControl();
};

