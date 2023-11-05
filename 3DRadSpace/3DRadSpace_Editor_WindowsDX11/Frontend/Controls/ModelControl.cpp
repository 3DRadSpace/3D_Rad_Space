#include "ModelControl.hpp"
#include "..\GDIFuncs.hpp"
#include "TextureControl.hpp"
#include "..\Windows\AssetManagerDialog.hpp"

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
		y,
		200,
		200,
		owner,
		nullptr,
		hInstance,
		nullptr
	))
{
	unsigned imageWidth;
	unsigned imageHeight;
	if (ModelReference.ID != 0)
		_image = loadImageFromFile((*content)[ModelReference]->Path.c_str(), imageWidth, imageHeight);
	else
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox,_image, imageWidth, imageHeight);
}

HWND ModelControl::GetPictureBox()
{
	return _pictureBox;
}

void ModelControl::HandleClick(HWND clickedHandle)
{
	if (clickedHandle == _pictureBox || clickedHandle == _button)
	{
		AssetManagerDialog assetManager(window, instance, _content);
		ModelReference = assetManager.ShowDialog<Engine3DRadSpace::Graphics::Model3D>();
		if (ModelReference.ID != 0)
		{
			unsigned w, h;
			_image = loadImageFromFile((*_content)[ModelReference]->Path.c_str(), w, h);
			SetImage(_pictureBox, _image, w, h);
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
