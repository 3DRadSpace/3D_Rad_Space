#pragma once
#include "Glyph.hpp"
#include "../../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics::Fonts
{
	class DLLEXPORT Font
	{
		class FontManager
		{
		public:
			FontManager();

			FontManager(FontManager&) = delete;
			FontManager(FontManager&&) = delete;
			FontManager& operator=(FontManager&) = delete;
			FontManager& operator=(FontManager&&) = delete;

			~FontManager();

			static FT_Library FreeTypeLib;
		};

		bool _valid;
		
		FT_Face _font;
		std::string _supportedCharacters;

		GraphicsDevice* _device;

		static FontManager _manager;

		std::vector<std::pair<Glyph, std::unique_ptr<Texture2D>>> _characters;
		unsigned _size;
	public:
		Font(GraphicsDevice* device, const std::string &path, unsigned size = 14, const char* supportedCharacters = nullptr);

		Font(Font&) = delete;
		Font(Font&& font) noexcept;

		Font& operator=(Font&) = delete;
		Font& operator=(Font&&) noexcept;

		unsigned Size() const;
		const std::string SupportedCharacters() const;

		Texture2D* operator[](int index);

		~Font();
	};
}