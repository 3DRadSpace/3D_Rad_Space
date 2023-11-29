#include "SkinmeshPreviewer.hpp"
#include <Engine3DRadSpace/Objects/Skinmesh.hpp>
#include <Engine3DRadSpace/Objects/Camera.hpp>
#include "../Frontend/Settings.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Math;

SkinmeshPreviewer::SkinmeshPreviewer(HWND owner, HINSTANCE hInstance, const std::filesystem::path &meshPath):
	Game(Engine3DRadSpace::Window(static_cast<void*>(hInstance), static_cast<void*>(owner)))
{
	_basicShader.reset(new BasicTextured(Device.get()));

	_skinmesh = std::make_unique<Skinmesh>("", true, "", meshPath);
	_skinmesh->Load(Content.get());

	for (auto& meshPart : *_skinmesh->GetModel())
	{
		for (auto& modelMeshPart : *meshPart)
		{
			modelMeshPart->SetShaders(_basicShader);
		}
	}

	_initialZoom = _skinmesh->GetModel()->GetBoundingSphere().Radius * 2.0f;

	Camera camera("");
	camera.LookAt = Vector3::Zero();

	camera.LookMode = Camera::CameraMode::UseLookAtCoordinates;
	auto cameraID = Objects.AddNew<Camera>(std::move(camera));

	_camera = static_cast<Camera*>(Objects[cameraID]);
}

void SkinmeshPreviewer::Update(Keyboard &keyboard, Mouse &mouse, double dt)
{
	_zoom = _initialZoom - mouse.ScrollWheel();
	if(mouse.LeftButton() == ButtonState::Pressed && Window->IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = mouse.Position();
		Window->SetMousePosition(screenCenter);

		Point pd = screenCenter - mousePos;
		Vector2 mouseDelta = static_cast<Vector2>(pd) * float(dt);
		_camCoords -= mouseDelta * Settings::CameraSensitivity.Value;

		_camCoords.Y = std::clamp<float>(
			_camCoords.Y,
			-std::numbers::pi_v<float> / 2.0f + std::numeric_limits<float>::epsilon(),
			std::numbers::pi_v<float> / 2.0f - std::numeric_limits<float>::epsilon()
		);
	}
	Quaternion q = Quaternion::FromYawPitchRoll(-_camCoords.Y, 0, 0)* Quaternion::FromYawPitchRoll(0, -_camCoords.X, 0);
	_camera->Position = _zoom * Vector3::UnitZ().Transform(q);
}

void SkinmeshPreviewer::Draw(Matrix4x4& view, Matrix4x4& projection, double dt)
{
	_skinmesh->Draw(view, projection, dt);
}
