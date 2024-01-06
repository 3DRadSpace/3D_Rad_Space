#pragma once
#include <Engine3DRadSpace/Graphics/Model3D.hpp>

template<typename T>
bool AssetRenderer(Engine3DRadSpace::GraphicsDevice *device, const std::string &imagePath, T *assetPtr) = delete;

template<> bool AssetRenderer<Engine3DRadSpace::Graphics::Texture2D>(
	Engine3DRadSpace::GraphicsDevice *device,
	const std::string &imagePath,
	Engine3DRadSpace::Graphics::Texture2D *texture
);

template<> bool AssetRenderer<Engine3DRadSpace::Graphics::Model3D>(
	Engine3DRadSpace::GraphicsDevice *device,
	const std::string &imagePath,
	Engine3DRadSpace::Graphics::Model3D *model
);