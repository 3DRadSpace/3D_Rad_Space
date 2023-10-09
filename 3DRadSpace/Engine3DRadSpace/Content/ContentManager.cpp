#include "ContentManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;

ContentManager::ContentManager(GraphicsDevice *device):
	_device(device),
	_lastID(1)
{
	_resources.push_back(nullptr); // ID 0 = nullptr
}

std::vector<std::unique_ptr<IAsset>>::iterator Engine3DRadSpace::Content::ContentManager::begin()
{
	return std::next(_resources.begin());
}

std::vector<std::unique_ptr<IAsset>>::iterator Engine3DRadSpace::Content::ContentManager::end()
{
	return _resources.end();
}

void ContentManager::RemoveAsset(const std::string &name)
{
	_resources.erase(std::remove_if(_resources.begin(), _resources.end(),
		[name](std::unique_ptr<IAsset> &asset) -> bool
		{
			return asset->Name == name;
		}
	), _resources.end());
}

void ContentManager::RemoveAsset(unsigned id)
{
	_resources.erase(std::remove_if(_resources.begin(), _resources.end(),
		[id](std::unique_ptr<IAsset> &asset) -> bool
	{
		return asset->ID() == id;
	}
	), _resources.end());
}

GraphicsDevice* Engine3DRadSpace::Content::ContentManager::GetDevice()
{
	return _device;
}
