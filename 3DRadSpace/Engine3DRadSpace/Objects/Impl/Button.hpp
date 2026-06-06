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
		Button();

		Button(Button&&) noexcept = default;
		Button& operator=(Button&&) noexcept = default;

		Math::RectangleF IdleTextureRect = Math::RectangleF(0, 0, 1, 1);
		Math::Color IdleClickColor = Math::Colors::White;

		Math::RectangleF HoverTextureRect = Math::RectangleF(0, 0, 1, 1);
		Math::Color HoverTintColor = Math::Colors::White;

		Math::RectangleF ClickTextureRect = Math::RectangleF(0, 0, 1, 1);
		Math::Color ClickTintColor = Math::Colors::White;

		void Update() override;

		Reflection::UUID GetUUID() const noexcept override;

		~Button() override = default;
	};
}