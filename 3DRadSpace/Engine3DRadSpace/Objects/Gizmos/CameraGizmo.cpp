#include "CameraGizmo.hpp"
#include "../../Graphics/IGraphicsDevice.hpp"
#include "../../Graphics/IGraphicsCommandList.hpp"
#include "../../Games/Game.hpp"
#include "../ObjectList.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Camera>::Gizmo()
{
	AllowScaling = false;
	Allow2DRendering = false;
}

void Gizmo<Camera>::Load()
{
	if(Object == nullptr) return;
	if(_wasLoaded) return;

	auto device = (static_cast<Camera*>(Object))->GetGraphicsDeviceHandle();

	if(_cameraModel == nullptr)
	{
		_cameraModel = std::make_unique<Model3D>(device, "Data\\Models\\Camera.x");
	}

	auto res = device->Resolution() / 4.0f;

	if(_cameraPreview == nullptr)
	{
		_cameraPreview = device->CreateRenderTarget(res.X, res.Y, PixelFormat::R32G32B32A32_Float);
	}

	if(_cameraPreviewDepth == nullptr)
	{
		_cameraPreviewDepth = device->CreateDepthStencilBuffer(res.X, res.Y);
	}

	if(_font == nullptr)
	{
		_font = std::make_unique<Font>(device, "Data\\Fonts\\Arial.ttf");
	}

	_wasLoaded = true;
}

void Gizmo<Camera>::Load(const std::filesystem::path& path)
{
}

void Gizmo<Camera>::Draw3D()
{
	if(Object == nullptr) return;

	auto camera = static_cast<Camera*>(Object);

	auto cameraModel = static_cast<Model3D*>(_cameraModel.get());
	
	auto game = static_cast<Game*>(Object->GetGame());

	auto model = Matrix4x4::CreateFromQuaternion(
		camera->Rotation * Quaternion::FromYawPitchRoll(std::numbers::pi_v<float>, 0, 0)
	) * Matrix4x4::CreateTranslation(camera->Position);

	auto view = game->View;
	auto proj = game->Projection;

	cameraModel->Draw(model * view * proj);
}

void Gizmo<Camera>::Draw2D()
{
	if(Object == nullptr) return;

	auto camera = static_cast<Camera*>(Object);
	auto game = static_cast<Game*>(Object->GetGame());
	auto view = game->View;
	auto proj = game->Projection;

	if(Selected)
	{
		auto oldView = view;
		auto oldProjection = proj;
		auto oldCamera = game->Objects->GetRenderingCamera();

		game->View = camera->GetViewMatrix();
		game->Projection = camera->GetProjectionMatrix();
		game->Objects->SetRenderingCamera(camera);

		auto cameraPreview = dynamic_cast<ITexture2D*>(_cameraPreview.get());
		auto cameraRT = static_cast<IRenderTarget*>(_cameraPreview.get());
		auto cameraPreviewDepth = static_cast<IDepthStencilBuffer*>(_cameraPreviewDepth.get());

		auto cmd = game->Device->ImmediateContext();

		cmd->SetRenderTargetAndDepth(cameraRT, cameraPreviewDepth);
		cmd->ClearRenderTarget(cameraRT);
		cmd->ClearDepthBuffer(cameraPreviewDepth);
		cmd->SetViewport(
			Viewport{
				RectangleF(0,0, cameraPreview->Width(), cameraPreview->Height()),
				0.0f,
				1.0f
			}
		);

		for(auto& obj : (*game->Objects))
		{
			if(obj.Object.get() == camera) continue;

			if(obj.InternalType == ObjectType::IObject3D)
			{
				static_cast<IObject3D*>(obj.Object.get())->Draw3D();
			}
		}

		cmd->SetViewport();
		cmd->SetRenderTargetAndDepth(nullptr, nullptr);

		game->SpriteBatch->End();
		game->SpriteBatch->Begin();
		game->SpriteBatch->DrawNormalized(
			cameraPreview,
			RectangleF(0.6f, 0.6f, 0.4f, 0.4f)
		);

		game->SpriteBatch->DrawString(
			static_cast<Font*>(_font.get()),
			camera->Name,
			Vector2(0.6f, 0.58f),
			1.0f
		);
		game->SpriteBatch->End();

		game->View = oldView;
		game->Projection = oldProjection;
		game->Objects->SetRenderingCamera(oldCamera);
	}
}

void Gizmo<Camera>::Update()
{
}

Gizmo<Camera>::~Gizmo()
{
}