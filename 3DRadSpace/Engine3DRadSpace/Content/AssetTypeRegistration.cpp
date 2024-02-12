#include "AssetTypeRegistration.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Model3D.hpp"
#include "../Tag.hpp"
#include "../Internal/AssetUUIDReader.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Internal;

//inline std::vector<std::pair<Reflection::UUID, AssetCtor>> Engine3DRadSpace::Internal::assetTypes;

Asset* Engine3DRadSpace::Content::CreateAssetInstance(Reflection::UUID nuuid, GraphicsDevice* device,const std::filesystem::path& path)
{
	if (Internal::assetTypes.empty())
	{
		RegisterAssetType<Graphics::Texture2D>();
		RegisterAssetType<Graphics::Model3D>();
	}

	for (auto& [uuid, ctor] : Internal::assetTypes)
	{
		if (uuid == nuuid) return ctor(device, path);
	}
	return nullptr;
}
