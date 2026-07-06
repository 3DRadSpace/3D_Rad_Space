#include "DirectionalLight.hpp"
#include "../../Graphics/Rendering/RenderingManager.hpp"
#include "../../Core/IGame.hpp"

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
	_light = new Rendering::DirectionalLight{
		.LightColor = lightColor,
		.AmbientColor = ambientColor,
		.LightDirection = direction,
		.Intensity = intensity
	};
}

void DirectionalLight::Initialize()
{
	if (_temporaryPointer && _light)
	{
		delete _light;
		_light = &(GetGame()->GetService<Rendering::RenderingManager>({})->MainLight);
		_temporaryPointer = false;
	}
}

void DirectionalLight::Load()
{
}

void DirectionalLight::Load(const std::filesystem::path& path)
{
}

void DirectionalLight::Update()
{
}

void DirectionalLight::SetLightDir(const Math::Vector3& direction) noexcept
{
	if (_light)
	{
		_light->LightDirection = direction;
	}
}

void DirectionalLight::SetLightColor(const Math::Color& color) noexcept
{
	if (_light)
	{
		_light->LightColor = color;
	}
}

void DirectionalLight::SetAmbientColor(const Math::Color& color) noexcept
{
	if (_light)
	{
		_light->AmbientColor = color;
	}
}
void DirectionalLight::SetIntensity(float intensity) noexcept
{
	if (_light)
	{
		_light->Intensity = intensity;
	}
}

Math::Vector3 DirectionalLight::GetLightDir() const noexcept
{
	return _light ? _light->LightDirection : Math::Vector3(0.0f, -1.0f, 0.0f);
}

Math::Color DirectionalLight::GetLightColor() const noexcept
{
	return _light ? _light->LightColor : Math::Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Math::Color DirectionalLight::GetAmbientColor() const noexcept
{
	return _light ? _light->AmbientColor : Math::Color(0.0f, 0.0f, 0.0f, 1.0f);
}

float DirectionalLight::GetIntensity() const noexcept
{
	return _light ? _light->Intensity : 1.0f;
}

Reflection::UUID DirectionalLight::GetUUID() const noexcept
{
	// {5F23C116-BB90-4246-9137-26B554289B4D}
	return { 0x5f23c116, 0xbb90, 0x4246, { 0x91, 0x37, 0x26, 0xb5, 0x54, 0x28, 0x9b, 0x4d } };
}

Gizmos::IGizmo* DirectionalLight::GetGizmo() const noexcept
{
	return nullptr;
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
REFL_END
