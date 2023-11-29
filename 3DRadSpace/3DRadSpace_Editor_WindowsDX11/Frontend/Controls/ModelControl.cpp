#include "ModelControl.hpp"
#include "..\GDIFuncs.hpp"
#include "TextureControl.hpp"
#include "..\Windows\AssetManagerDialog.hpp"
#include "..\Windows\SkinmeshPreviewDialog.hpp"

ModelControl::ModelControl(
	HWND owner,
	HINSTANCE hInstance, 
	Engine3DRadSpace::Content::ContentManager* content,
	Engine3DRadSpace::Reflection::RefModel3D model,
	const std::string& name,
	int x,
	int y 
) : 
	AssetControl(owner, hInstance, x, y, content),
	_pictureBox(CreateWindowExA(
		0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_REALSIZECONTROL,
		x,
		y + _cy + 5,
		200,
		200,
		owner,
		nullptr,
		hInstance,
		nullptr
	))
{
	_cy += 205;

	unsigned imageWidth;
	unsigned imageHeight;
	if (ModelReference.ID != 0)
		_image = loadImageFromFile((*content)[ModelReference]->Path.c_str(), imageWidth, imageHeight);
	else
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox,_image, imageWidth, imageHeight);

	constexpr const char* previewBtnText = "Preview";

	HDC hdc = GetDC(owner);
	SIZE textSize;
	GetTextExtentPointA(hdc, previewBtnText, int(strlen(previewBtnText)), &textSize);

	_previewButton = CreateWindowExA(
		0,
		"Button",
		previewBtnText,
		WS_VISIBLE | WS_CHILD,
		x + 10,
		y + _cy,
		200,
		textSize.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cy += textSize.cy + 5;
}

HWND ModelControl::GetPictureBox()
{
	return _pictureBox;
}

void ModelControl::HandleClick(HWND clickedHandle)
{
	if (clickedHandle == _pictureBox || clickedHandle == _button)
	{
		AssetManagerDialog assetManager(owner, instance, _content);
		ModelReference = assetManager.ShowDialog<Engine3DRadSpace::Graphics::Model3D>();
		if (ModelReference.ID != 0)
		{
			unsigned w, h;
			_image = loadImageFromFile((*_content)[ModelReference]->Path.c_str(), w, h);
			SetImage(_pictureBox, _image, w, h);
		}
	}
	if (clickedHandle == _previewButton)
	{
		if (ModelReference.ID != 0)
		{
			SkinmeshPreviewDialog previewer(owner, instance, std::filesystem::path(_content->operator[]<Engine3DRadSpace::Graphics::Model3D>(ModelReference)->Path));
			previewer.ShowDialog();
		}
	}
}

ModelControl::~ModelControl()
{
	if (_image != nullptr)
	{
		DeleteObject(_image);
		_image = nullptr;
	}
}
