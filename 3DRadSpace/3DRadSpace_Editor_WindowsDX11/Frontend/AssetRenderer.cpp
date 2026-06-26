#include "AssetRenderer.hpp"
#include <Engine3DRadSpace\Graphics\Model3D.hpp>
#include <Engine3DRadSpace\Math\Matrix4x4.hpp>
#include <Engine3DRadSpace\Graphics\SpriteBatch.hpp>
#include <Engine3DRadSpace\Core\IGame.hpp>
#include <Engine3DRadSpace\Graphics\Rendering\RenderingManager.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Content::Assets;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

template<> bool AssetRenderer(IGraphicsDevice *device, const std::string &imagePath, TextureAsset *texture)
{
	if(device && texture)
	{
		texture->Get()->SaveToFile(imagePath);
		return true;
	}
	else return false;
}

template<> bool AssetRenderer(IGraphicsDevice *device, const std::string &imagePath, ModelAsset *modelAsset)
{
	using std::ranges::views::iota;

	auto model = modelAsset->Get();

	if(device && model)
	{
		auto boundingSphere = model->GetBoundingSphere();
		auto cmd = device->ImmediateContext();

		for (auto&& n : iota(0, 3))
		{
			cmd->Clear(Colors::Gray);
			
			auto view =
				Matrix4x4::CreateLookAtView(
					boundingSphere.Center + ((boundingSphere.Radius + 0.5f) *
						Vector3(
							float(cos(-std::numbers::pi / 4)),
							0,
							float(sin(-std::numbers::pi / 4))
						)),
					Vector3::Zero(),
					Vector3::UnitY()
				);

			auto projection = Matrix4x4::CreatePerspectiveProjection(4.f / 3.f, 65, 0.01f, 500.0f);

			auto renderingManager = device->GetOwner()->GetService<Rendering::RenderingManager>({});
			
			for (auto& modelMesh : *model)
			{
				for (auto& modelMeshPart : *modelMesh)
				{
					modelMeshPart->View = view;
					modelMeshPart->Projection = projection;

					renderingManager->Batcher.Submit(modelMeshPart.get(), Rendering::RenderPassType::Opaque);
				}
			}
			
		}

		cmd->SaveBackBufferToFile(imagePath);
		return true;
	}
	return false;
}

template<>
bool AssetRenderer(IGraphicsDevice* device, const std::string& imagePath, FontAsset* fontAsset)
{
	using std::ranges::views::iota;
	auto font = fontAsset->Get();
	
	if (device && font)
	{
		SpriteBatch spriteBatch(device);

		for (auto&& n : iota(0, 3))
		{
			spriteBatch.Begin();
			spriteBatch.DrawString(font, "The quick brown fox jumps over the lazy dog", Point(20), 1);
			spriteBatch.End();
		}
		device->ImmediateContext()->SaveBackBufferToFile(imagePath);
	}
	return false;
}

template<>
bool AssetRenderer(IGraphicsDevice* device, const std::string& imagePath, SkyboxAsset* skyboxAsset)
{
	auto skybox = skyboxAsset->Get();

	skybox->View = Matrix4x4::CreateLookAtView(
		Vector3(-1, 0, -1),
		Vector3::Zero(),
		Vector3::UnitY()
	);

	skybox->Projection = Matrix4x4::CreatePerspectiveProjection(4.f / 3.f, 65, 0.01f, 500.0f);

	if (device && skybox)
	{
		auto cmd = device->ImmediateContext();
		 
		for (auto&& n : std::ranges::views::iota(0, 3))
		{
			cmd->Clear();
			skybox->Draw3D();
			cmd->Present();
		}

		cmd->SaveBackBufferToFile(imagePath);
		return true;
	}
	return false;
}