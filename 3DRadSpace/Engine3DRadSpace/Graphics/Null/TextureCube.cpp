#include "TextureCube.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Null;

TextureCube::TextureCube(GraphicsDevice* device, const std::filesystem::path& filePath)
{
	(void)device;
	(void)filePath;
}

TextureCube::TextureCube(GraphicsDevice* device, const std::array<ITexture2D*, 6> &cubeMap)
{
	(void)device;
	(void)cubeMap;
}

Math::UPoint TextureCube::Size() const noexcept
{
	return Math::UPoint();
}

unsigned TextureCube::Width() const noexcept
{
	return 0;
}

unsigned TextureCube::Height() const noexcept
{
	return 0;
}

void* TextureCube::GetViewHandle() const noexcept
{
	return nullptr;
}

std::unique_ptr<ITextureCube> TextureCube::CreateStaging()
{
	return std::make_unique<TextureCube>(nullptr, std::filesystem::path());
}

size_t TextureCube::ReadData(size_t subResource, void** data)
{
	(void)subResource;
	(void)data;

	return 0;
}

void TextureCube::SetData(size_t subResource, void* data, size_t buffSize)
{
	(void)subResource;
	(void)data;
	(void)buffSize;
}

void TextureCube::EndRead(size_t subResource)
{
	(void)subResource;
}

void* TextureCube::GetHandle() const noexcept
{
	return nullptr;
}

IGraphicsDevice* TextureCube::GetGraphicsDevice() const noexcept
{
	return nullptr;
}