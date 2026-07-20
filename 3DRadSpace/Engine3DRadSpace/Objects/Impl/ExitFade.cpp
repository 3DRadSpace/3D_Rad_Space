#include "ExitFade.hpp"
#include "../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

ExitFade::ExitFade(const std::string& name, const std::filesystem::path& projectPath, Color fadeColor, float fadeTime) :
	IObject2D(name, false),
	ProjectPath(projectPath.string()),
	FadeColor(fadeColor),
	FadeTime(fadeTime)
{
}

void ExitFade::Update()
{
	if(!Enabled) return;
}

void ExitFade::Draw2D()
{
	if(!Enabled) return;
	auto game = static_cast<Game*>(_game);

	_timer += game->Draw_dt;

	if(_timer >= FadeTime)
	{
		if(ProjectPath.empty())
			_game->Exit();
		else
		{
			game->AppendScene(ProjectPath);
		}
	}
}

void ExitFade::Initialize()
{
}

void ExitFade::Load()
{
}

void ExitFade::Load(const std::filesystem::path& path)
{
	ProjectPath = path.string();
}

Reflection::UUID ExitFade::GetUUID() const noexcept
{
	// {1243BB88-6FF5-43AD-97D6-8907FAE54528}
	return { 0x1243bb88, 0x6ff5, 0x43ad, { 0x97, 0xd6, 0x89, 0x7, 0xfa, 0xe5, 0x45, 0x28 } };
}

Gizmos::IGizmo* ExitFade::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(ExitFade, "ExitFade", "Events", "Loads an other scene, or exits the game")
	REFL_FIELD(ExitFade, std::string, Name, "Name", "ExitFade", "Object name")
	REFL_FIELD(ExitFade, std::string, ProjectPath, "Path to new project", "", "Project to load, empty if closing the game")
	REFL_FIELD(ExitFade, Color, FadeColor, "Fade color", Colors::Black, "Fade out color")
	REFL_FIELD(ExitFade, float, FadeTime, "Fade time", 5.0f, "Fade out time")
	REFL_METHOD(ExitFade, void, &ExitFade::Enable, "Activate")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/ExitFade.html")
REFL_END