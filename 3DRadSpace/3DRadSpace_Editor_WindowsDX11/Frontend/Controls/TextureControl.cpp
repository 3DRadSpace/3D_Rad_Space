#include "TextureControl.hpp"
#include "..\GDIFuncs.hpp"
#include "..\Windows\AssetManagerDialog.hpp"

TextureControl::TextureControl(
	HWND owner,
	HINSTANCE hInstance,
	Engine3DRadSpace::Content::ContentManager *content,
	unsigned texture,
	const std::string &name,
	int x,
	int y
) :
	AssetControl(owner, hInstance, x, y + 205, content),
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
	)),
	_image(nullptr)
{
	unsigned imageWidth;
	unsigned imageHeight;

	if(AssetReference != 0)
		_image = loadImageFromFile(_content->GetAssetPath(AssetReference).string(), imageWidth, imageHeight);
	else
		_image = loadImageFromFile("Data\\NoAsset.png", imageWidth, imageHeight);

	SetImage(_pictureBox,_image, imageWidth, imageHeight);

	_cy += 205;
}

void SetImage(HWND _pictureBox, HBITMAP _image, unsigned imageWidth, unsigned imageHeight)
{
	float r_wh = float(imageWidth) / imageHeight;

	SendMessageA(_pictureBox, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(_image));
	SetWindowPos(_pictureBox, nullptr, 0, 0, int(200 * r_wh), 200, SWP_NOMOVE);
}


TextureControl::TextureControl(TextureControl &&c) noexcept:
	AssetControl(c),
	_pictureBox(c._pictureBox),
	_image(c._image)
{
	AssetReference = c.AssetReference;

	c._image = nullptr;
	c._pictureBox = nullptr;
	c.AssetReference = 0;
}

TextureControl &TextureControl::operator=(TextureControl &&c) noexcept
{
	this->window = c.window;
	this->instance = c.instance;
	this->owner = c.owner;
	_label = c._label;
	_textBox = c._textBox;
	_button = c._button;
	_pictureBox = c._pictureBox;
	_image = c._image;
	AssetReference = c.AssetReference;

	c.window = nullptr;
	c.instance = nullptr;
	c.owner = nullptr;
	c._label = nullptr;
	c._textBox = nullptr;
	c._button = nullptr;
	c._pictureBox = nullptr;
	c._image = nullptr;
	c.AssetReference = 0;

	return *this;
}

HWND TextureControl::GetPixturebox()
{
	return _pictureBox;
}

TextureControl::~TextureControl()
{
	if(_image != nullptr)
	{
		DeleteObject(_image);
		_image = nullptr;
	}
}

void TextureControl::HandleClick(HWND clickedWindow)
{
	if(clickedWindow == _pictureBox || clickedWindow == _button)
	{
		AssetManagerDialog assetManager(this->owner, this->instance, _content);
		auto r = assetManager.ShowDialog<Engine3DRadSpace::Graphics::Texture2D>();

		if(r.ID != 0)
		{
			unsigned w;
			unsigned h;
			_image = loadImageFromFile(_content->GetAssetPath(r.ID).string(), w, h);
			SetImage(_pictureBox,_image, w, h);

			AssetReference = r.ID;
		}
	}
}
