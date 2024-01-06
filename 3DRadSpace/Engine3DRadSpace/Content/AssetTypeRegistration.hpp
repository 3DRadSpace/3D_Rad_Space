#pragma once
#include "Asset.hpp"

namespace Engine3DRadSpace::Internal
{
	typedef Content::Asset* (*AssetCtor)(GraphicsDevice* device, const std::filesystem::path& path);
	inline std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, Engine3DRadSpace::Internal::AssetCtor>> assetTypes;
}

namespace Engine3DRadSpace::Content
{
	template<AssetType T>
	Asset* CreateAssetInstance(GraphicsDevice* device, std::filesystem::path& path)
	{
		return new T(device, path);
	}

	template<AssetType T>
	bool RegisterAssetType()
	{
		for (auto& [uuid, ctor] : Internal::assetTypes)
		{
			if (uuid == Internal::AssetUUIDReader::GetUUID(Tag<T>()))
				return false;
		}
		Internal::assetTypes.emplace_back(Internal::AssetUUIDReader::GetUUID(Tag<T>()), reinterpret_cast<Internal::AssetCtor>(CreateAssetInstance<T>));
		return true;
	}
}