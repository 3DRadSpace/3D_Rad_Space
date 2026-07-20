#include "Skybox.hpp"
#include "../Games/Game.hpp"
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "Gizmos.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

Skybox::Skybox(const std::string& name, bool visible, RefSkybox skybox) :
	IObject3D(name, visible),
	SkyboxID(skybox),
	_skybox(nullptr)
{
}

Skybox::Skybox(const std::string& name, bool visible, const std::filesystem::path& path) :
	IObject3D(name, visible),
	_path(std::make_unique<std::string>(path.string())),
	SkyboxID(0),
	_skybox(nullptr)
{
}

void Skybox::Initialize()
{
}

void Skybox::Update()
{
}

void Skybox::Load()
{
	auto game = static_cast<Game*>(_game);

	if(_path)
	{
		_skybox = game->Content->Load<SkyboxAsset>(*_path);
		_path.reset();
	}
	if(SkyboxID)
	{
		_skybox = game->Content->operator[](SkyboxID);
	}
}

void Skybox::Load(const std::filesystem::path& path)
{
	auto game = static_cast<Game*>(_game);
	_skybox = game->Content->Load<SkyboxAsset>(path.string());
}

Reflection::UUID Skybox::GetUUID() const noexcept
{
	// {E29253F1-2053-4752-ADBF-236AA6A0039E}
	return { 0xe29253f1, 0x2053, 0x4752, { 0xad, 0xbf, 0x23, 0x6a, 0xa6, 0xa0, 0x3, 0x9e } };
}

void Skybox::Draw3D()
{
	auto game = static_cast<Game*>(_game);

	if(_skybox && Visible)
	{
		auto camera = game->Objects->GetRenderingCamera();

		auto viewMatrix = camera->GetViewMatrix();
		viewMatrix.M41 = 0;
		viewMatrix.M42 = 0;
		viewMatrix.M43 = 0;

		(*_skybox)->Transform = viewMatrix * camera->GetProjectionMatrix();
		(*_skybox)->Draw3D();
	}
}

float Skybox::Intersects(const Math::Ray& r)
{
	return std::numeric_limits<float>::signaling_NaN();
}

Gizmos::IGizmo* Skybox::GetGizmo() const noexcept
{
	return Internal::GizmoOf<Skybox>(this);
}

REFL_BEGIN(Skybox, "Skybox", "3D Objects", "3D sky box")
	REFL_FIELD(Skybox, std::string, Name, "Name", "Skybox", "Name of the object")
	REFL_FIELD(Skybox, bool, Visible, "Visible", true, "Is the object visible")
	REFL_FIELD(Skybox, RefSkybox, SkyboxID, "Skybox ID", 0, "ID of the skybox asset")
	REFL_METHOD(Skybox, void, &Skybox::Show, "Show")
	REFL_METHOD(Skybox, void, &Skybox::Hide, "Hide")
	REFL_METHOD(Skybox, bool, &Skybox::SwitchVisibility, "Switch Visibility")
	REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/Skybox.html")
REFL_END