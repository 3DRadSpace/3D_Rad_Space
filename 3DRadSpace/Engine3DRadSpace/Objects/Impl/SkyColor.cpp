#include "SkyColor.hpp"
#include "../Games/Game.hpp"
#include "Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

SkyColor::SkyColor(const std::string& name, bool enabled, Color color):
	IObject(name, enabled, enabled)
{
}

void SkyColor::Initialize()
{
}

void SkyColor::Update()
{
	auto game = static_cast<Game*>(_game);

	if(Enabled) 
		game->ClearColor = Colour;
}

void SkyColor::Load()
{
}

void SkyColor::Load(const std::filesystem::path& path)
{
}

Reflection::UUID SkyColor::GetUUID() const noexcept
{
	// {EEA241C5-99C5-4A41-9E65-F673888CEBC4}
	return { 0xeea241c5, 0x99c5, 0x4a41, { 0x9e, 0x65, 0xf6, 0x73, 0x88, 0x8c, 0xeb, 0xc4 } };
}

Gizmos::IGizmo* SkyColor::GetGizmo() const noexcept
{
	auto gizmo = Internal::GizmoOf<SkyColor>(this);
	gizmo->Allow2DRendering = gizmo->Allow3DRendering = false;
	gizmo->AllowUpdating = true;
	return gizmo;
}

REFL_BEGIN(SkyColor,"SkyColor", "Rendering", "Sets the backbuffer clear color")
	REFL_FIELD(SkyColor, std::string, Name, "Name", "SkyColor", "Object of the name")
	REFL_FIELD(SkyColor, bool, Enabled, "Enabled", true, "Does the backround color get set every frame?")
	REFL_FIELD(SkyColor, Color, Colour, "Color", Colors::Black, "Back buffer clear color")
	REFL_METHOD(SkyColor, void, &SkyColor::Enable, "Enable")
	REFL_METHOD(SkyColor, void, &SkyColor::Disable, "Disable")
	REFL_METHOD(SkyColor, bool, &SkyColor::Switch, "Switch")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/SkyColor.html")
REFL_END