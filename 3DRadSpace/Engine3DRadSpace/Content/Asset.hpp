#pragma once
#include "IAsset.hpp"
#include "../Graphics/Model3D.hpp"

namespace Engine3DRadSpace::Content
{
	template<AssetType T>
	class Asset : public IAsset
	{
		std::unique_ptr<T> _asset;
	public:
		Asset(GraphicsDevice *device, const std::string &path) :
			IAsset( 0, typeid(T), path, "")
		{
			_asset = std::make_unique<T>(device, path);
		}

		template<typename ...Args>
		Asset(GraphicsDevice* device, const std::string& path, Args&& ...params) :
			IAsset(0, typeid(T), path, "")
		{
			_asset = std::make_unique<T>(device, path, std::forward<Args>(params)...);
		}

		Asset(Asset &) = delete;
		Asset(Asset &&) noexcept = delete;

		Asset &operator=(Asset &) = default;
		Asset &operator=(Asset &&) noexcept = default;

		virtual void *Get()
		{
			return _asset.get();
		}
	};
}