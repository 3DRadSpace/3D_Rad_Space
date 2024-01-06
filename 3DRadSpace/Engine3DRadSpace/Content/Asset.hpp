#pragma once
#include "../GraphicsDevice.hpp"
#include "../Reflection/UUID.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT Asset
	{
	protected:
		Asset() = default;
	public:
		virtual Reflection::UUID GetUUID() = 0;
		virtual ~Asset() = default;
	};

	template<typename T>
	concept AssetType = std::is_base_of_v<Asset, T> &&
		(std::is_constructible_v<T, GraphicsDevice*, const std::string&> || std::is_constructible_v<T, GraphicsDevice*, const std::filesystem::path&>);
}