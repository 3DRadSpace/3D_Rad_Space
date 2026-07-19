#include "Sprite.hpp"
#include "../Games/Game.hpp"
#include "Gizmos.hpp"
#include "Gizmos/SpriteGizmo.hpp"
#include "../../Math/Math.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

Sprite::Sprite() :
	IObject2D("Sprite", true, true),
	FlipU(false),
	FlipV(false),
	Image(0),
	TintColor(Colors::White),
	_texture(nullptr)
{
	_initEvents();
}

Sprite::Sprite(
	const std::string &name,
	bool visible,
	const std::string &path, 
	const Vector2& pos,
	const Vector2& scale, 
	float depth, 
	const Vector2& pivot,
	float rotation, 
	bool flipU, 
	bool flipV, 
	const Color& tintColor
) :
	Sprite(name, visible, RefTexture2D(0), pos, scale, depth, pivot, rotation, flipU, flipV, tintColor)
{
	_tempResourceString = std::make_unique<std::string>(path);
	_initEvents();
}

Sprite::Sprite(
	const std::string &name, 
	bool visible, 
	RefTexture2D resource, 
	const Vector2 &pos, 
	const Vector2 &scale,
	float depth, 
	const Vector2 &pivot,
	float rotation, 
	bool flipU,
	bool flipV,
	const Color &tintColor
) :
	IObject2D(name, visible, visible, Vector2(pos.X, pos.Y), scale, rotation, pivot, depth),
	FlipU(flipU),
	FlipV(flipV),
	Image(resource),
	TintColor(tintColor),
	_texture(nullptr)
{
	_initEvents();
}

void Sprite::_initEvents()
{
}

ITexture2D* Sprite::GetSpriteImage()
{
	return _texture;
}

void Sprite::SetSpriteImage(Graphics::ITexture2D* texture)
{
	_texture = texture;
	Image = 0;
}

void Sprite::Initialize()
{
}

void Sprite::Load()
{
	auto game = static_cast<Game*>(_game);

	if(_tempResourceString != nullptr)
	{
		_texture = game->Content->Load<TextureAsset>(*_tempResourceString)->Get();
		_tempResourceString.reset();
	}
	else _texture = static_cast<TextureAsset*>((game->Content->operator[](Image)))->Get();
}

void Sprite::Load(const std::filesystem::path &path)
{
	auto game = static_cast<Game*>(_game);

	_texture = game->Content->Load<TextureAsset>(path, &Image)->Get();
}

void Sprite::Update()
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
			OnMouseEnter.InvokeAll(std::span<Any>{});
			_hover = true;
		}

		if(game->Mouse.LeftButton() == ButtonState::Pressed && !_click)
		{
			OnClick.InvokeAll(std::span<Any>{});
			_click = true;
		}
		else if(game->Mouse.LeftButton() == ButtonState::Released) _click = false;
	}
	else
	{
		if(_hover)
		{
			OnMouseLeave.InvokeAll(std::span<Any>{});
			_hover = false;
			_click = false;
		}
	}
}

void Sprite::Draw2D()
{
	if(!Visible) return;

	FlipMode flip = (FlipU ? FlipMode::FlipHorizontally : FlipMode::None) | (FlipV ? FlipMode::FlipVertically : FlipMode::None);
	
	auto game = static_cast<Game*>(_game);
	game->SpriteBatch->DrawNormalized(
		_texture, 
		RectangleF(Position.X, Position.Y, Scale.X, Scale.Y),
		UVCoordinates, 
		TintColor,
		Rotation,
		flip,
		Depth
	);
}

Reflection::UUID Sprite::GetUUID() const noexcept
{
	// {90239EA1-D02D-424C-90BB-15ABC5E5D55D}
	return Reflection::UUID{0x90239ea1, 0xd02d, 0x424c, { 0x90, 0xbb, 0x15, 0xab, 0xc5, 0xe5, 0xd5, 0x5d }};
}

Gizmos::IGizmo* Sprite::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Sprite>(this);
}

bool Sprite::IsHovered() const noexcept
{
	return _hover;
}

bool Sprite::IsClicked() const noexcept
{
	return _click;
}

void Sprite::ResetInputState() noexcept
{
	_hover = false;
	_click = false;
}

REFL_BEGIN(Sprite, "Sprite", "2D Objects", "A single drawable image")
	REFL_FIELD(Sprite, std::string, Name, "Name", "Sprite", "Object's name")
	REFL_FIELD(Sprite, bool, Visible, "Enabled", true, "Is the sprite visible?")
	REFL_FIELD(Sprite, RefTexture2D, Image, "Image", 0, "Sprite image reference")
	REFL_FIELD(Sprite, Vector2, Position, "Position", Vector2::Zero(), "Sprite position in normalized 2D coordinates.")
	REFL_FIELD(Sprite, Vector2, Scale, "Scale", Vector2(0.25, 0.25), "Sprite scale in normalized 3D coordinates.")
	REFL_FIELD(Sprite, float, Depth, "Depth", 0.0f, "Sprite Z-depth")
	REFL_FIELD(Sprite, float, Rotation, "Rotation", 0.0f, "Sprite rotation in degrees")
	REFL_FIELD(Sprite, bool, FlipU, "Flip horizontally", false, "Is the sprite image flipped horizontally?")
	REFL_FIELD(Sprite, bool, FlipV, "Flip vertically", false, "Is the sprite image flipped vertically?")
	REFL_FIELD(Sprite, Color, TintColor, "Tint Color", Colors::White, "Tint color")
REFL_END