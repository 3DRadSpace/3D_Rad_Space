#include "Sprite.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

Sprite::Sprite() :
	IObject2D("Sprite", "...", true, true),
	FlipU(false),
	FlipV(false),
	Image(0),
	TintColor(Colors::Black),
	_texture(nullptr)
{
}

Sprite::Sprite(const std::string &name, bool visible, const std::string &path, const Vector2 &pos, const Vector2 &scale, const Vector2& pivot,
               float depth, float rotation, bool flipU, bool flipV, const Color &tintColor) :
	IObject2D(name, "...", visible, visible, Vector2(pos.X, pos.Y), scale, rotation, pivot, depth),
	FlipU(flipU),
	FlipV(FlipV),
	TintColor(tintColor),
	_texture(nullptr)
{
	_tempResourceString = std::make_unique<std::string>(path);
}

Sprite::Sprite(const std::string &name, bool visible, RefTexture2D resource, const Vector2 &pos, const Vector2 &scale, float depth, const Vector2 &pivot,
               float rotation, bool flipU, bool flipV, const Color &tintColor) :
	IObject2D(name, "...", visible, visible, Vector2(pos.X, pos.Y), scale, rotation, pivot, depth),
	FlipU(flipU),
	FlipV(flipV),
	Image(resource),
	TintColor(tintColor),
	_texture(nullptr)
{
}

Texture2D* Sprite::GetSpriteImage()
{
	return _texture;
}

void Sprite::Initialize()
{
}

void Sprite::Load(Content::ContentManager *content)
{
	if(_tempResourceString != nullptr)
	{
		_texture = content->Load<Texture2D>(*_tempResourceString.get());
		_tempResourceString.reset();
	}
	else _texture = static_cast<Texture2D *>((content->operator[](Image))->Get());
}

void Sprite::Load(Content::ContentManager* content, const std::filesystem::path &path)
{
	_tempResourceString = std::make_unique<std::string>(path.string());
	Load(content);
}


void Sprite::Update(Keyboard&keyboard, Mouse&mouse, double dt)
{
}

void Sprite::Draw(SpriteBatch *spriteBatch, double dt)
{
	FlipMode flip = (FlipU ? FlipMode::FlipHorizontally : FlipMode::None) | (FlipV ? FlipMode::FlipVertically : FlipMode::None);
	spriteBatch->DrawNormalized(_texture, RectangleF(Position.X, Position.Y, Scale.X, Scale.Y), Engine3DRadSpace::Math::RectangleF(0,0,1,1), TintColor, Rotation, flip, Depth);
}

void Sprite::EditorInitialize()
{
}

void Sprite::EditorLoad(Content::ContentManager *content)
{
	auto asset = content->operator[](Image);
	if(asset != nullptr) _texture = static_cast<Texture2D *>(asset->Get());
	else _texture = content->Load<Texture2D>("Data//NoAsset.png");
}

void Sprite::EditorDraw(SpriteBatch *spriteBatch, double dt, bool selected)
{
	Color nTint = selected ? Colors::Red : TintColor;
	FlipMode flip = (FlipU ? FlipMode::FlipHorizontally : FlipMode::None) | (FlipV ? FlipMode::FlipVertically : FlipMode::None);
	spriteBatch->DrawNormalized(_texture, RectangleF(Position.X, Position.Y, Scale.X, Scale.Y), Engine3DRadSpace::Math::RectangleF(0, 0, 1, 1), TintColor, Rotation, flip, Depth);
}

Reflection::UUID Sprite::GetUUID()
{
	// {90239EA1-D02D-424C-90BB-15ABC5E5D55D}
	return Reflection::UUID{0x90239ea1, 0xd02d, 0x424c, { 0x90, 0xbb, 0x15, 0xab, 0xc5, 0xe5, 0xd5, 0x5d }};
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

void testFn()
{
	Sprite spr;

}