#include "Sprite.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Reflection;

Sprite::Sprite() :
	IObject("Sprite", "...", true, true)
{
}

Engine3DRadSpace::Objects::Sprite::Sprite(const std::string &name, bool visible, const std::string &path, const Vector2 &pos, const Vector2 &scale,
	float depth, float rotation, bool flipU, bool flipV) :
	IObject(name, "...", visible, visible, Vector3(pos.X, pos.Y, depth), Vector3::Zero(), Quaternion(rotation,0,0,0), Vector3(scale.X, scale.Y,0)),
	FlipU(flipU),
	FlipV(FlipV)
{
	_tempResourceString = std::make_unique<std::string>(path);
}

Engine3DRadSpace::Objects::Sprite::Sprite(const std::string &name, bool visible, Reflection::RefTexture2D resource, const Vector2 &pos, const Vector2 &scale,
	float depth, float rotation, bool flipU, bool flipV) :
	IObject(name, "...", visible, visible, Vector3(pos.X, pos.Y, depth), Vector3::Zero(), Quaternion(rotation, 0, 0, 0), Vector3(scale.X, scale.Y, 0)),
	FlipU(flipU),
	FlipV(FlipV),
	Image(resource)
{

}

void Sprite::Initialize() 
{

}

void Sprite::Load(Content::ContentManager *content)
{
	if(_tempResourceString != nullptr)
	{
		content->Load<Texture2D>(*_tempResourceString.get());
		_tempResourceString.reset();
	}
}

void Sprite::Update(Input::Keyboard &keyboard, Input::Mouse &mouse, double dt)
{
}

void Sprite::Draw(Matrix &view, Matrix &projection, double dt)
{

}

void Sprite::EditorInitialize()
{
}

void Sprite::EditorDraw(const Matrix &view, const Matrix &projection, double dt, bool selected)
{
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
	REFL_FIELD(Sprite, Vector3, Position, "Position", Vector3::Zero(), "Sprite position in normalized 2D coordinates. Z is depth")
	REFL_FIELD(Sprite, float, Rotation, "Rotation", 0.0f, "Sprite rotation in degrees")
	REFL_FIELD(Sprite, bool, FlipU, "Flip horizontally", false, "Is the sprite image flipped horizontally?")
	REFL_FIELD(Sprite, bool, FlipV, "Flip vertically", false, "Is the sprite image flipped vertically?")
REFL_END
