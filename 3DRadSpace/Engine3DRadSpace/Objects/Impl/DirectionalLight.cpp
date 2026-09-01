#include "DirectionalLight.hpp"
#include "../../Graphics/Rendering/RenderingManager.hpp"
#include "../../Core/IGame.hpp"
#include "../Gizmos.hpp"
#include "../Gizmos/DirectionalLightGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Graphics;

DirectionalLight::DirectionalLight(
	const std::string& name,
	bool visible,
	const Math::Vector3& direction,
	const Math::Color& lightColor,
	const Math::Color& ambientColor,
	float intensity
) : IObject(name, true, visible)
{
	_temporaryPointer = true;
}

void DirectionalLight::Initialize()
{
	if (_temporaryPointer && !_light)
	{
		_light = &(GetGame()->GetService<Rendering::RenderingManager>({})->MainLight);
		_temporaryPointer = false;
	}

	Update();
}

void DirectionalLight::Load()
{
}

void DirectionalLight::Load(const std::filesystem::path& path)
{
}

void DirectionalLight::Update()
{
	if (Visible) Sync();
}

void DirectionalLight::SetLightDir(const Math::Vector3& direction) noexcept
{
	auto normalizedDir = Math::Vector3::Normalize(direction);
	if (_light)
	{
		_light->LightDirection = normalizedDir;
	}
	_lightCpy.LightDirection = normalizedDir;
}

void DirectionalLight::SetLightColor(const Math::Color& color) noexcept
{
	if (_light)
	{
		_light->LightColor = color;
	}
	_lightCpy.LightColor = color;
}

void DirectionalLight::SetAmbientColor(const Math::Color& color) noexcept
{
	if (_light)
	{
		_light->AmbientColor = color;
	}
	_lightCpy.AmbientColor = color;
}
void DirectionalLight::SetIntensity(float intensity) noexcept
{
	if (_light)
	{
		_light->Intensity = intensity;
	}
	_lightCpy.Intensity = intensity;
}

Math::Vector3 DirectionalLight::GetLightDir() const noexcept
{
	return _lightCpy.LightDirection;
}

Math::Color DirectionalLight::GetLightColor() const noexcept
{
	return _lightCpy.LightColor;
}

Math::Color DirectionalLight::GetAmbientColor() const noexcept
{
	return _lightCpy.AmbientColor;
}

float DirectionalLight::GetIntensity() const noexcept
{
	return _lightCpy.Intensity;
}

void DirectionalLight::Sync() noexcept
{
	if (_light && Visible)
	{
		_light->LightDirection = GetLightDir();
		_light->LightColor = GetLightColor();
		_light->AmbientColor = GetAmbientColor();
		_light->Intensity = GetIntensity();
	}
}

Reflection::UUID DirectionalLight::GetUUID() const noexcept
{
	// {5F23C116-BB90-4246-9137-26B554289B4D}
	return { 0x5f23c116, 0xbb90, 0x4246, { 0x91, 0x37, 0x26, 0xb5, 0x54, 0x28, 0x9b, 0x4d } };
}

Gizmos::IGizmo* DirectionalLight::GetGizmo() const noexcept
{
	return Internal::GizmoOf<DirectionalLight>(this);
}

static void dl_setlightdir(DirectionalLight& dl, const Math::Vector3& dir) { dl.SetLightDir(dir); }
static Math::Vector3 dl_getlightdir(DirectionalLight& dl) { return dl.GetLightDir(); }

static void dl_setlightcolor(DirectionalLight& dl, const Math::Color& color) { dl.SetLightColor(color); }
static Math::Color dl_getlightcolor(DirectionalLight& dl) { return dl.GetLightColor(); }

static void dl_setambientcolor(DirectionalLight& dl, const Math::Color& color) { dl.SetAmbientColor(color); }
static Math::Color dl_getambientcolor(DirectionalLight& dl) { return dl.GetAmbientColor(); }

static void dl_setintensity(DirectionalLight& dl, const float& intensity) { dl.SetIntensity(intensity); }
static float dl_getintensity(DirectionalLight& dl) { return dl.GetIntensity(); }

REFL_BEGIN(DirectionalLight, "DirectionalLight", "Lighting", "A directional light source for the scene")
REFL_FIELD(DirectionalLight, std::string, Name, "Name", "DirectionalLight", "Name of the directional light object")
REFL_FIELD(DirectionalLight, bool, Visible, "Visible", true, "Is the directional light visible in the scene?")
REFL_FIELD_GS(DirectionalLight, Math::Vector3, dl_getlightdir, dl_setlightdir, "Direction", Math::Vector3(0.0f, -1.0f, 0.0f), "Direction of the light")
REFL_FIELD_GS(DirectionalLight, Math::Color, dl_getlightcolor, dl_setlightcolor, "Light Color", Math::Color(1.0f, 1.0f, 1.0f), "Color of the light")
REFL_FIELD_GS(DirectionalLight, Math::Color, dl_getambientcolor, dl_setambientcolor, "Ambient Color", Math::Color(0.1f, 0.1f, 0.1f), "Ambient color of the light")
REFL_FIELD_GS(DirectionalLight, float, dl_getintensity, dl_setintensity, "Intensity", 1.0f, "Intensity of the light")
REFL_METHOD(DirectionalLight, void, (&DirectionalLight::Show), "Show")
REFL_METHOD(DirectionalLight, void, (&DirectionalLight::Hide), "Hide")
REFL_METHOD(DirectionalLight, bool, (&DirectionalLight::SwitchVisibility), "Switch Visibility")
REFL_ATTR("HelpURL", "https://3dradspace.github.io/Docs/DirectionalLight.html")
REFL_ATTR("Icon", "Data\\Editor\\OBJ_DirectionalLight.png")
REFL_END
