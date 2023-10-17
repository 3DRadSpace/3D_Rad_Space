#include "AssetRenderer.hpp"
#include <Engine3DRadSpace/Math/Matrix.hpp>
#include <Engine3DRadSpace/Graphics/Shaders/BasicTextured_NBT.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;

template<> bool AssetRenderer(GraphicsDevice *device, const std::string &imagePath, Texture2D *texture)
{
	if(device && texture)
	{
		texture->SaveToFile(imagePath);
		return true;
	}
	else return false;
}

template<> bool AssetRenderer(GraphicsDevice *device, const std::string &imagePath, Model3D *model)
{
	if(device && model)
	{
		std::shared_ptr<BasicTextured_NBT> shader = std::make_shared<BasicTextured_NBT>(device);

		auto boundingSphere = model->GetBoundingSphere();

		model->SetShader(shader);
		model->Draw(
			Matrix(),
			Matrix::CreateLookAtView(
				boundingSphere.Center + ((boundingSphere.Radius + 2) * 
				Vector3(
					float(cos(std::numbers::pi / 4)),
					0,
					float(sin(std::numbers::pi / 4))
				)),
				Vector3::Zero(),
				Vector3::UnitY()
			),
			Matrix::CreatePerspectiveProjection(4.f / 3.f, 65, 0.01f, 500.0f)
		);

		device->SaveBackBufferToFile(imagePath);
		return true;
	}
	return false;
}