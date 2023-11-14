#include "Font.hpp"

#include "../PixelFormat.hpp"
#include "../../Logging/Exception.hpp"
#include "../Texture2D.hpp"

using namespace Engine3DRadSpace::Graphics::Fonts;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;

FT_Library Font::FontManager::FreeTypeLib;

Font::FontManager::FontManager()
{
	if (FT_Init_FreeType(&FreeTypeLib))
	{
		throw Exception("Failed to load the FreeType library!");
	}
}

Font::FontManager::~FontManager()
{
	FT_Done_FreeType(FreeTypeLib);
}

Font::FontManager Font::_manager;

Font::Font(GraphicsDevice* device, const std::string& path, unsigned size, const char* supportedCharacters):
	_device(device)
{
	if(FT_New_Face(FontManager::FreeTypeLib, path.c_str(), 0, &_font))
	{
		throw Exception("Failed to load font " + path + " !");
	}

	FT_Set_Pixel_Sizes(_font, 0, size);

	std::string characters(supportedCharacters != nullptr ? supportedCharacters : "");
	if(supportedCharacters == nullptr)
	{
		char defaultSupportedCharacters[256] = {};
		for(int i = 0; i < 255; i++)
		{
			defaultSupportedCharacters[i] = i + 1;
		}
		characters = defaultSupportedCharacters;
	}

	for(auto c : characters)
	{
		if(FT_Load_Char(_font, c, FT_LOAD_RENDER))
		{
			throw Exception(std::string("Character ") + c + " not supported by font " + path);
		}

		auto width = _font->glyph->bitmap.width;
		auto height = _font->glyph->bitmap.rows;
		auto fontBitmapBuffer = _font->glyph->bitmap.buffer;

		_characters.emplace_back(
			Glyph
			{
				.Character = c,
				.Size = Point{static_cast<int>(width), static_cast<int>(height)},
				.Bearing = Point{_font->glyph->bitmap_left, _font->glyph->bitmap_top},
				.Advance = static_cast<unsigned>(_font->glyph->advance.x)
			},
			//Texture2D(GraphicsDevice*, void, unsigned, unsigned, PixelFormat);
			std::make_unique<Texture2D>(_device, fontBitmapBuffer, width, height, PixelFormat::R8_SignedInt)
		);
	}
}

Font::Font(Font&& font) noexcept :
	_valid(font._valid),
	_font(font._font),
	_device(font._device),
	_characters(std::move(font._characters)),
	_size(font._size)
{
	font._font = { };
	font._valid = false;
	font._device = nullptr;
	font._size = 0;
}

Font& Font::operator=(Font&& font) noexcept
{
	_valid = font._valid;
	_font = font._font;
	_device = font._device;
	_characters = std::move(font._characters);
	_size = font._size;

	return* this;
}

Font::~Font()
{
	if(_valid)
		FT_Done_Face(_font);
}