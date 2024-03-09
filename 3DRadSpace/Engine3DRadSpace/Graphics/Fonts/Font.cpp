#include "Font.hpp"

#include "../PixelFormat.hpp"
#include "../../Logging/Exception.hpp"
#include "../Texture2D.hpp"

using namespace Engine3DRadSpace::Graphics::Fonts;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Graphics;

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
	_device(device),
	_size(size),
	_supportedCharacters(supportedCharacters != nullptr ? supportedCharacters : "")
{
	if(FT_New_Face(FontManager::FreeTypeLib, path.c_str(), 0, &_font))
	{
		throw Exception("Failed to load font " + path + " !");
	}

	FT_Set_Pixel_Sizes(_font, 0, size);

	if(supportedCharacters == nullptr)
	{
		char defaultSupportedCharacters[128] = {}; 
		const char offset = ' ';
		for (char i = offset; i < '~'; i++)
		{
			defaultSupportedCharacters[i - offset] = i;
		}
		_supportedCharacters = defaultSupportedCharacters;
	}

	for(auto c : _supportedCharacters)
	{
		if (FT_Load_Char(_font, c, FT_LOAD_RENDER) != 0)
			continue;

		auto width = _font->glyph->bitmap.width;
		auto height = _font->glyph->bitmap.rows;
		auto fontBitmapBuffer = _font->glyph->bitmap.buffer;

		auto glyph = Glyph
		{
			.Character = c,
			.Size = Point{static_cast<int>(width), static_cast<int>(height)},
			.Bearing = Point{_font->glyph->bitmap_left, _font->glyph->bitmap_top},
			.Advance = static_cast<unsigned>(_font->glyph->advance.x)
		};

		//TODO: Use a font "megatexture" instead of one texture for each character for performance reasons.
		[[likely]] if(fontBitmapBuffer != nullptr)
		{
			std::unique_ptr<float[]> glyphBuffer = std::make_unique<float[]>(width * height);

			for (size_t j = 0; j < height; j++)
			{
				for (size_t i = 0; i < width; i++)
				{
					auto p = (j * width) + i;
					glyphBuffer[p] = static_cast<float>(*(_font->glyph->bitmap.buffer)) / 255.0f;
				}
			}

			_characters.emplace_back(glyph, std::make_unique<Texture2D>(_device, glyphBuffer.get(), width, height, PixelFormat::R32_Float));
		}
		else
		{
			//create a transparent texture.
			std::array<Color, 4> transparentColors = { 0 };
			_characters.emplace_back(glyph, std::make_unique<Texture2D>(_device, transparentColors, 2, 2));
		}
	}
	_valid = true;
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

	font._valid = false;

	return* this;
}

unsigned Font::Size() const
{
	return _size;
}

const std::string Font::SupportedCharacters() const
{
	return _supportedCharacters;
}

Texture2D* Font::operator[](char chr)
{
	for (auto& [glyph, ptr] : this->_characters)
	{
		if (glyph.Character == chr) 
			return ptr.get();
	}
	return nullptr;
}

Font::~Font()
{
	if (_valid)
	{
		FT_Done_Face(_font);
		_valid = false;
	}
}