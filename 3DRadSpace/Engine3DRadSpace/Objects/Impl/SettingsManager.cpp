#include "SettingsManager.hpp"
#include "../../Games/Game.hpp"	

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

SettingsManager::SettingsManager(
	const std::string& name,
	const Point& screenRes,
	bool vsyncEnabled,
	bool fullscreenEnabled
) : IObject(name), Resolution(screenRes), VSyncEnabled(vsyncEnabled), FullscreenEnabled(fullscreenEnabled)
{
}

void SettingsManager::Initialize()
{
	auto game = static_cast<Game*>(GetGame());
	if (game->IsEditor()) return;

	auto context = game->Device->ImmediateContext();

	if (game->Device->Resolution() != Resolution)
	{
		context->ResizeBackBuffer(Resolution);
	}

	if (context->IsFullScreen() != FullscreenEnabled)
	{
		context->SetFullScreen(FullscreenEnabled);
	}

	game->Device->EnableVSync = VSyncEnabled;
}

void SettingsManager::Load()
{
}

void SettingsManager::Load(const std::filesystem::path& path)
{
}

void SettingsManager::Update()
{
}

Reflection::UUID SettingsManager::GetUUID() const noexcept
{
	// {88C432AA-2376-49CB-82A4-DF37E5D2F5A5}
	return { 0x88c432aa, 0x2376, 0x49cb, { 0x82, 0xa4, 0xdf, 0x37, 0xe5, 0xd2, 0xf5, 0xa5 } };
}

Gizmos::IGizmo* SettingsManager::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(SettingsManager, "SettingsManager", "Others", "Manages game settings such as resolution, fullscreen mode, and VSync")
REFL_FIELD(SettingsManager, std::string, Name, "Name", "Settings", "Object name")
REFL_FIELD(SettingsManager, Point, Resolution, "Resolution", Point(800, 600), "Backbuffer resolution")
REFL_FIELD(SettingsManager, bool, VSyncEnabled, "VSyncEnabled", true, "Whether to enable VSync or not")
REFL_FIELD(SettingsManager, bool, FullscreenEnabled, "FullscreenEnabled", false, "Whether to enable fullscreen mode or not")
REFL_METHOD(SettingsManager, void, &SettingsManager::Initialize, "Apply")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/SettingsManager.html")
REFL_END