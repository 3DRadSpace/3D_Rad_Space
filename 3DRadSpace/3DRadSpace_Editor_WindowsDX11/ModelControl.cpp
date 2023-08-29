#include "ModelControl.hpp"
#include "GDIFuncs.hpp"
#include "TextureControl.hpp"

ModelControl::ModelControl(
	HWND owner,
	HINSTANCE hInstance, 
	Engine3DRadSpace::Content::ContentManager* content,
	Engine3DRadSpace::Reflection::RefModel3D model,
	const std::string& name,
	int x,
	int y 
) : 
	AssetControl(owner, hInstance, x, y, content)
{
	_pictureBox = CreateWindowExA(
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
	);

	unsigned imageWidth;
	unsigned imageHeight;
	if (ModelReference.ID != 0)
		_image = loadImageFromFile((*content)[ModelReference]->Path.c_str(), imageWidth, imageHeight);
	else
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox,_image, imageWidth, imageHeight);
}

void ModelControl::HandleClick(HWND clickedHandle)
{
	if (_pictureBox == clickedHandle)
	{
		
	}
}
