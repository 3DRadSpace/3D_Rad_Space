#pragma once
#include "Asset.hpp"

#include "../Graphics/Model3D.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Internal/AssetUUIDReader.hpp"

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

	DLLEXPORT Asset* CreateAssetInstance(Reflection::UUID uuid, GraphicsDevice* device,const std::filesystem::path& path);

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

	template<typename R, typename Fn, typename ...Args>
	std::optional<R> AssetVisit(Reflection::UUID asset_uuid, Fn &&callable, Args&& ...args)
	{
		for (auto& [uuid, ctor] : Internal::assetTypes)
		{
			if (uuid == asset_uuid)
				return callable(std::forward<Args>(args)...);
		}
		return {};
	}

	template<typename Fn, typename ...Args>
	void AssetVisit(Reflection::UUID asset_uuid, Fn&& callable, Args&& ...args)
	{
		for (auto& [uuid, ctor] : Internal::assetTypes)
		{
			if (uuid == asset_uuid)
				callable(std::forward<Args>(args)...);
		}
	}
}