#pragma once
#include "../IObject2D.hpp"
#include "../../Reflection/Reflection.hpp"
#include "../../Content/Assets/TextureAsset.hpp"
#include "../../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	using RefTexture2D = Content::AssetID<Content::Assets::TextureAsset>;

	/// <summary>
	/// Represents a 2D sprite that can be drawn on the screen, with support for mouse hover and click interaction.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Sprite : public IObject2D
	{
		std::unique_ptr<std::string> _tempResourceString;
		void _initEvents();
	protected:
		Graphics::ITexture2D* _texture;
		bool _hover;
		bool _click;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		Sprite();
		/// <summary>
		/// Constructs a sprite from a file path.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="path">File path to the texture</param>
		/// <param name="pos">Position of the sprite</param>
		/// <param name="scale">Scale of the sprite</param>
		/// <param name="depth">Draw depth of the sprite</param>
		/// <param name="pivot">Pivot point of the sprite</param>
		/// <param name="rotation">Rotation of the sprite, in radians</param>
		/// <param name="flipU">Flip the sprite horizontally</param>
		/// <param name="flipV">Flip the sprite vertically</param>
		/// <param name="tintColor">Tint colour applied to the sprite</param>
		Sprite(
			const std::string &name,
			bool visible,
			const std::string &path, 
			const Math::Vector2& pos,
			const Math::Vector2& scale, 
			float depth = 0.0,
			const Math::Vector2& pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Math::Color& tintColor = Math::Colors::White
		);

		/// <summary>
		/// Constructs a sprite from a numerical asset identifier.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="visible">Is this object visible?</param>
		/// <param name="resource">Numerical asset identifier for the texture</param>
		/// <param name="pos">Position of the sprite</param>
		/// <param name="scale">Scale of the sprite</param>
		/// <param name="depth">Draw depth of the sprite</param>
		/// <param name="pivot">Pivot point of the sprite</param>
		/// <param name="rotation">Rotation of the sprite, in radians</param>
		/// <param name="flipU">Flip the sprite horizontally</param>
		/// <param name="flipV">Flip the sprite vertically</param>
		/// <param name="tintColor">Tint colour applied to the sprite</param>
		Sprite(
			const std::string &name,
			bool visible,
			RefTexture2D resource, 
			const Math::Vector2 &pos,
			const Math::Vector2& scale,
			float depth = 0.0,
			const Math::Vector2 &pivot = Math::Vector2::Zero(),
			float rotation = 0.0f,
			bool flipU = false,
			bool flipV = false,
			const Math::Color &tintColor = Math::Colors::White
		);

		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;

		/// <summary>
		/// Flip the sprite horizontally.
		/// </summary>
		bool FlipU;
		/// <summary>
		/// Flip the sprite vertically.
		/// </summary>
		bool FlipV;

		/// <summary>
		/// Numerical reference to the texture asset used by this object.
		/// </summary>
		RefTexture2D Image;
		/// <summary>
		/// Gets the underlying texture used by this sprite.
		/// </summary>
		/// <returns>Pointer to the underlying texture</returns>
		Graphics::ITexture2D *GetSpriteImage();
		/// <summary>
		/// Sets the underlying texture used by this sprite.
		/// </summary>
		/// <param name="texture">Pointer to the texture</param>
		void SetSpriteImage(Graphics::ITexture2D* texture);

		/// <summary>
		/// Tint colour applied to the sprite.
		/// </summary>
		Math::Color TintColor;
		/// <summary>
		/// UV coordinates used to sample the sprite's texture.
		/// </summary>
		Math::RectangleF UVCoordinates = Math::RectangleF(0, 0, 1, 1);

		/// <summary>
		/// Executes when the sprite is clicked. Return value is ignored.
		/// </summary>
		Reflection::Event OnClick;
		/// <summary>
		/// Executes when the mouse cursor enters the sprite's bounds. Return value is ignored.
		/// </summary>
		Reflection::Event OnMouseEnter;
		/// <summary>
		/// Executes when the mouse cursor leaves the sprite's bounds. Return value is ignored.
		/// </summary>
		Reflection::Event OnMouseLeave;

		/// <summary>
		/// Gets whether the sprite is currently hovered by the mouse cursor.
		/// </summary>
		/// <returns>True if hovered, false otherwise</returns>
		bool IsHovered() const noexcept;
		/// <summary>
		/// Gets whether the sprite is currently clicked.
		/// </summary>
		/// <returns>True if clicked, false otherwise</returns>
		bool IsClicked() const noexcept;
		/// <summary>
		/// Resets the hover and click input state of the sprite.
		/// </summary>
		void ResetInputState() noexcept;

		/// <summary>
		/// Sets up the input events (OnClick, OnMouseEnter, OnMouseLeave).
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Loads the texture asset.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Loads a texture from a specified path.
		/// </summary>
		/// <param name="path">Image file</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Updates the hover and click input state of the sprite.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Draws the sprite.
		/// </summary>
		void Draw2D() override;

		/// <summary>
		/// Gets the UUID of the Sprite type.
		/// </summary>
		/// <returns>{90239EA1-D02D-424C-90BB-15ABC5E5D55D}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns the gizmo associated with this object.
		/// </summary>
		/// <returns>Pointer to the gizmo</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;

		virtual ~Sprite() = default;
	};
}

REFL_FWD(Sprite)