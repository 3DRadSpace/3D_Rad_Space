#include "TextureControl.hpp"

TextureControl::TextureControl(
	HWND owner,
	HINSTANCE hInstance,
	Engine3DRadSpace::Content::ContentManager *content,
	Engine3DRadSpace::Reflection::RefTexture2D texture,
	const std::string &name,
	int x,
	int y
):
	AssetControl(owner, hInstance, x, y),
	TextureReference(texture)
{
	_pictureBox = CreateWindowExA(
		0,
		"Static",
		"",
		WS_VISIBLE | WS_CHILD | SS_BITMAP,
		x,
		y + _cy + 25,
		100,
		100,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_image = nullptr;
	if(TextureReference.ID != 0)
		_image = LoadBitmapA(nullptr, (*content)[TextureReference]->Path.c_str());
	else
		_image = LoadBitmapA(nullptr, "Data\\NoAsset.png");

	SendMessageA(_pictureBox, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(_image));
}

TextureControl::TextureControl(TextureControl &&c) noexcept:
	AssetControl(c),
	_image(c._image),
	_pictureBox(c._pictureBox),
	TextureReference(c.TextureReference)
{
	c._image = nullptr;
	c._pictureBox = nullptr;
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
	TextureReference = c.TextureReference;

	c.window = nullptr;
	c.instance = nullptr;
	c.owner = nullptr;
	c._label = nullptr;
	c._textBox = nullptr;
	c._button = nullptr;
	c._pictureBox = nullptr;
	c._image = nullptr;
	c.TextureReference = Engine3DRadSpace::Reflection::RefTexture2D(0);

	return *this;
}

HWND TextureControl::GetPixturebox()
{
	return _pictureBox;
}

TextureControl::~TextureControl()
{
	if(_image != nullptr)DeleteObject(_image);
}
