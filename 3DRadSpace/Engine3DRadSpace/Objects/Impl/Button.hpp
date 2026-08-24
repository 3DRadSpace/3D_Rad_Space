#pragma once
#include "Sprite.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a clickable sprite, that has different UV coordinates for button states.
	/// </summary>
	/// <remarks>
	/// 
	/// </remarks>
	class E3DRSP_OBJECTS_IMPL_EXPORT Button : public Sprite
	{
	public:
		/// <summary>
		/// Creates a button with default values. The button will be invisible and disabled by default.
		/// </summary>
		Button();

		Button(Button&&) noexcept = default;
		Button& operator=(Button&&) noexcept = default;
		/// <summary>
		/// UV coordinates for the idle state of the button. The default value is (0, 0, 1, 1), which represents the entire texture.
		/// </summary>
		Math::RectangleF IdleTextureRect = Math::RectangleF(0, 0, 1, 1);
		/// <summary>
		/// Button color for the idle state of the button. The default value is white, which means no color tinting will be applied to the texture.
		/// </summary>
		Math::Color IdleClickColor = Math::Colors::White;
		/// <summary>
		/// UV coordinates for the hover state of the button. The default value is (0, 0, 1, 1), which represents the entire texture.
		/// </summary>
		Math::RectangleF HoverTextureRect = Math::RectangleF(0, 0, 1, 1);
		///<summary>
		/// Button color for the hover state of the button. The default value is white, which means no color tinting will be applied to the texture.
		///</summary>
		Math::Color HoverTintColor = Math::Colors::White;
		/// <summary>
		/// UV coordinates for the click state of the button. The default value is (0, 0, 1, 1), which represents the entire texture.
		/// </summary>
		Math::RectangleF ClickTextureRect = Math::RectangleF(0, 0, 1, 1);
		/// <summary>
		/// Button color for the click state of the button. The default value is white, which means no color tinting will be applied to the texture.
		/// </summary>
		Math::Color ClickTintColor = Math::Colors::White;
		/// <summary>
		/// Update the button state based on mouse input and trigger events accordingly.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Returns an unique type identifier for the Button class.
		/// </summary>
		/// <returns>Button type UUID</returns>
		Reflection::UUID GetUUID() const noexcept override;

		~Button() override = default;
	};
}