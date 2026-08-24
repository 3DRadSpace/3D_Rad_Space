#pragma once
#include "../IObject2D.hpp"
#include "../../Graphics/Font.hpp"
#include "../../Content/AssetID.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Content/Assets/FontAsset.hpp"

namespace Engine3DRadSpace::Objects
{ 
	using RefFont = Content::AssetID<Content::Assets::FontAsset>;

	/// <summary>
	/// Represents a 2D text object that can be drawn on the screen using a specified font.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT TextPrint : public IObject2D
	{
	private:
		Graphics::Font* _font = nullptr;
		std::unique_ptr<std::string> _path;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		TextPrint();
		/// <summary>
		/// Constructs a text object from a numerical asset identifier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="font">Numerical asset identifier for the font</param>
		/// <param name="text">Text to display</param>
		/// <param name="pos">Position of the text</param>
		/// <param name="rotation">Rotation of the text, in radians</param>
		/// <param name="scale">Scale of the text</param>
		/// <param name="color">Colour of the text</param>
		/// <param name="depth">Draw depth of the text</param>
		TextPrint(
			const std::string& name, 
			bool visible,
			RefFont font,
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale, 
			Math::Color color, 
			float depth
		);
		/// <summary>
		/// Constructs a text object from a file path.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="font">File path to the font</param>
		/// <param name="text">Text to display</param>
		/// <param name="pos">Position of the text</param>
		/// <param name="rotation">Rotation of the text, in radians</param>
		/// <param name="scale">Scale of the text</param>
		/// <param name="color">Colour of the text</param>
		/// <param name="depth">Draw depth of the text</param>
		TextPrint(
			const std::string& name,
			bool visible,
			const std::filesystem::path &font, 
			const std::string& text,
			const Math::Vector2& pos,
			float rotation,
			float scale,
			Math::Color color,
			float depth
		);

		TextPrint(TextPrint&&) noexcept = default;
		TextPrint& operator=(TextPrint&&) noexcept = default;

		/// <summary>
		/// Numerical reference to the font asset used by this object.
		/// </summary>
		RefFont Font = 0;
		/// <summary>
		/// Colour of the text.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		/// Text to display.
		/// </summary>
		std::string Text;

		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Loads the font asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads a font from a specified path.
		/// </summary>
		/// <param name="path">Font file</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Gets the UUID of the TextPrint type.
		/// </summary>
		/// <returns>{12B25ECE-A980-4A58-9388-872AEA9FD2B5}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Draws the text.
		/// </summary>
		void Draw2D() override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		/// <summary>
		/// Gets the underlying font used by this object.
		/// </summary>
		/// <returns>Pointer to the underlying font</returns>
		Graphics::Font* GetFont() const noexcept;
	};
}

REFL_FWD(TextPrint)