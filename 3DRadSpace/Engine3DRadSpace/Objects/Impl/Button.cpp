#include "Button.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Button::Button() :
	Sprite("Button", true, RefTexture2D(0), Vector2(0,0), Vector2(1,1), 0, Vector2(0.5f, 0.5f), 0, false, false, Colors::White)
{
	UVCoordinates = IdleTextureRect;
	TintColor = IdleClickColor;
}

void Button::Update()
{
	if(!Enabled) return;

	auto game = static_cast<Game*>(_game);
	auto mousePosNorm = static_cast<Vector2>(game->Mouse.Position());
	auto wndSize = static_cast<Vector2>(game->Window->Size());

	auto normMousePos = Vector2(mousePosNorm.X / wndSize.X, mousePosNorm.Y / wndSize.Y);
	auto spriteRect = RectangleF(Position.X, Position.Y, Scale.X, Scale.Y);

	if(spriteRect.Contains(normMousePos))
	{
		if(!_hover)
		{
			OnMouseEnter.InvokeAll(std::span<Reflection::Any>());
			UVCoordinates = HoverTextureRect;
			TintColor = HoverTintColor;
			_hover = true;
		}

		if(game->Mouse.LeftButton() == ButtonState::Pressed && !_click)
		{
			OnClick.InvokeAll(std::span<Reflection::Any>());
			UVCoordinates = ClickTextureRect;
			TintColor = ClickTintColor;
			_click = true;
		}
		else if(game->Mouse.LeftButton() == ButtonState::Released)
		{
			_click = false;
			UVCoordinates = HoverTextureRect;
			TintColor = HoverTintColor;
		}
	}
	else
	{
		if(_hover)
		{
			OnMouseLeave.InvokeAll(std::span<Reflection::Any>());
			_hover = false;
			_click = false;
		
			UVCoordinates = IdleTextureRect;
			TintColor = IdleClickColor;
		}
	}
}

Reflection::UUID Button::GetUUID() const noexcept
{
	// {DB3CD706-4598-4228-8DD0-46B27601B674}
	return {0xdb3cd706, 0x4598, 0x4228, { 0x8d, 0xd0, 0x46, 0xb2, 0x76, 0x1, 0xb6, 0x74 }};
}