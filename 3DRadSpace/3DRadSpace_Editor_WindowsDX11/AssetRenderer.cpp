#include "AssetRenderer.hpp"
#include <Engine3DRadSpace/Math/Matrix.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
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
		model->Draw(
			Matrix(),
			Matrix::CreateLookAtView(
				Vector3(
					cos(std::numbers::pi / 4),
					0,
					sin(std::numbers::pi / 4)
				),
				Vector3::Zero(),
				Vector3::UnitY()
			),
			Matrix::CreatePerspectiveProjection(4.f / 3.f, 65, 0.01f, 500.0f)
		);

		device->SaveBackBufferToFile(imagePath);
		return true;
	}
}