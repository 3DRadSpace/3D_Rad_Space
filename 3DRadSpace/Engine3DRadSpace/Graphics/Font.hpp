#pragma once
#include "Glyph.hpp"
#include "IGraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	class IGraphicsDevice;

	/// <summary>
	/// Represents a Font.
	/// </summary>
	/// <remarks>
	/// Fonts are being loaded using FreeType.
	/// When loading fonts, a single texture is created containing all supported characters. The texture is trivially packed (in a left-right, up-down order).
	/// </remarks>
	class E3DRSP_GRAPHICS_EXPORT Font
	{
		class FontManager
		{
		public:
			FontManager();

			FontManager(const FontManager&) = delete;
			FontManager(FontManager&&) = delete;
			FontManager& operator=(const FontManager&) = delete;
			FontManager& operator=(FontManager&&) = delete;

			~FontManager();
		};

		bool _valid;
		
		void* _font;
		std::string _supportedCharacters;

		IGraphicsDevice* _device;

		static FontManager _manager;
	
		std::vector<std::pair<Glyph, Math::Rectangle>> _glyphs;
		std::unique_ptr<ITexture2D> _texture;
		unsigned _size;
	public:
		/// <summary>
		/// Constructs a Font type, with specified size and supported characters.
		/// </summary>
		/// <param name="device">Graphics device</param>
		/// <param name="path">TTF Font path.</param>
		/// <param name="size">Font size</param>
		/// <param name="supportedCharacters">A C-style string of supported characters.</param>
		Font(IGraphicsDevice* device, const std::filesystem::path &path, unsigned size, const char* supportedCharacters = nullptr);
		/// <summary>
		/// Loads a TTF font.
		/// </summary>
		/// <param name="device">Graphics Device</param>
		/// <param name="path">TTF font file path</param>
		Font(IGraphicsDevice* device, const std::filesystem::path &path);

		Font(const Font&) = delete;
		/// <summary>
		/// Move constructor. Transfers the ownership of the given Font instance to this instance.
		/// </summary>
		/// <param name="font">The Font to move from.</param>
		Font(Font&& font) noexcept;

		Font& operator=(const Font&) = delete;
		/// <summary>
		/// Move assignment operator. 
		/// </summary>
		/// <param name="other">The Font to move from.</param>
		/// <returns>The moved Font.</returns>
		Font& operator=(Font&& other) noexcept;

		/// <summary>
		/// Returns the size the font was created with.
		/// </summary>
		/// <returns>Font size.</returns>
		unsigned Size() const noexcept;
		/// <summary>
		/// Returns a copy of the supported characters.
		/// </summary>
		/// <returns>A string containing the supported characters.</returns>
		const std::string SupportedCharacters() const noexcept;

		/// <summary>
		/// Returns the texture containing all glyphs.
		/// </summary>
		/// <returns>The texture containing all glyphs.</returns>
		ITexture2D* GetTexture() const noexcept;

		/// <summary>
		/// Gets the glyph of a specific character.
		/// </summary>
		/// <param name="chr">Character.</param>
		/// <returns>Nullopt if that character is not supported.</returns>
		std::optional<Glyph> GetCharGlyph(char chr) const noexcept;
		/// <summary>
		/// Gets the source rectangle of a specified character.
		/// </summary>
		/// <param name="chr">Character.</param>
		/// <returns>Nullopt if that character is not supported.</returns>
		std::optional<Math::Rectangle> GetCharSourceRectangle(char chr) const noexcept;

		~Font();
	};
}