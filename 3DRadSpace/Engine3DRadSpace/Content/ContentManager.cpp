#include "ContentManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

ContentManager::ContentManager(GraphicsDevice *device):
	_device(device),
	_lastID(1)
{
	_assets.emplace_back(nullptr);
}

void Engine3DRadSpace::Content::ContentManager::Reload(unsigned id)
{

}

std::filesystem::path Engine3DRadSpace::Content::ContentManager::GetAssetPath(unsigned id)
{
	return _assets[id].Path;
}

std::vector<ContentManager::AssetEntry>::iterator ContentManager::begin()
{
	return std::next(_assets.begin());
}

std::vector<ContentManager::AssetEntry>::iterator ContentManager::end()
{
	return _assets.end();
}

void ContentManager::RemoveAsset(unsigned id)
{
	_assets.erase(_assets.begin() + id);
}

GraphicsDevice* ContentManager::GetDevice()
{
	return _device;
}