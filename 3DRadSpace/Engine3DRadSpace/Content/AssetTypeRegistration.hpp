#pragma once
#include "Asset.hpp"

#include "../Graphics/Model3D.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Internal/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Internal
{
	typedef Content::IAsset* (*AssetCtor)(GraphicsDevice* device, const std::filesystem::path& path);
	inline std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, Engine3DRadSpace::Internal::AssetCtor>> assetTypes;
}

namespace Engine3DRadSpace::Content
{
	template<AssetType T>
	IAsset* CreateAssetInstance(GraphicsDevice* device, std::filesystem::path& path)
	{
		return new T(device, path);
	}

	DLLEXPORT IAsset* CreateAssetInstance(Reflection::UUID uuid, GraphicsDevice* device,const std::filesystem::path& path);

	template<AssetType T>
	bool RegisterAssetType()
	{
		for (auto& [uuid, ctor] : Internal::assetTypes)
		{
			if (uuid == Internal::AssetUUIDReader::GetUUID(Tag<T>()))
				return false;
		}
		Internal::assetTypes.emplace_back(Internal::AssetUUIDReader::GetUUID(Tag<T>()),
			[](GraphicsDevice* device, const std::filesystem::path& path) -> Content::IAsset*
			{
				return static_cast<Content::IAsset*>(new T(device, path));
			}								  
		);
		return true;
	}
}