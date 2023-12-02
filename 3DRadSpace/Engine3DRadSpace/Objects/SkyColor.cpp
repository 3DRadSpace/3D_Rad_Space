#include "SkyColor.hpp"
#include "../Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

SkyColor::SkyColor(const std::string& name, bool enabled, const std::string& tag, Color color):
	IObject2D(name, tag, enabled, enabled)
{
}

void SkyColor::Initialize()
{
}

void SkyColor::Update(Input::Keyboard& keyboard, Input::Mouse& mouse, double dt)
{
}

void SkyColor::Load(Content::ContentManager* content)
{
}

void SkyColor::Load(Content::ContentManager* content, const std::filesystem::path& path)
{
}

void SkyColor::EditorInitialize()
{
}

void SkyColor::EditorLoad(Content::ContentManager* content)
{
}

Reflection::UUID SkyColor::GetUUID()
{
	// {EEA241C5-99C5-4A41-9E65-F673888CEBC4}
	return { 0xeea241c5, 0x99c5, 0x4a41, { 0x9e, 0x65, 0xf6, 0x73, 0x88, 0x8c, 0xeb, 0xc4 } };
}

void SkyColor::Draw(Graphics::SpriteBatch* spriteBatch, double dt)
{
	_game->ClearColor = Colour;
}

void SkyColor::EditorDraw(Graphics::SpriteBatch* spriteBatch, double dt, bool selected)
{
	_game->ClearColor = Colour;
}

REFL_BEGIN(SkyColor,"SkyColor", "Rendering", "Sets the backbuffer clear color")
	REFL_FIELD(SkyColor, std::string, Name, "Name", "SkyColor", "Object of the name")
	REFL_FIELD(SkyColor, bool, Enabled, "Enabled", true, "Does the backround color get set every frame?")
	REFL_FIELD(SkyColor, Color, Colour, "Color", Colors::Black, "Back buffer clear color")
REFL_END