#pragma once
#include "../GraphicsDevice.hpp"
#include "../Reflection/UUID.hpp"

namespace Engine3DRadSpace::Internal
{
	struct AssetUUIDReader;
}

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT IAsset
	{
	protected:
		IAsset() = default;
	public:
		virtual Reflection::UUID GetUUID() = 0;
		virtual ~IAsset() = default;
	};

	template<typename T>
	concept AssetType = std::is_base_of_v<IAsset, T> &&
		(std::is_constructible_v<T, GraphicsDevice*, const std::string&> || std::is_constructible_v<T, GraphicsDevice*, const std::filesystem::path&>);
}