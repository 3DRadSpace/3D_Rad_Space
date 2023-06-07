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
		Asset(GraphicsDevice *device, const std::string &path)
		{
			_asset = std::make_unique<T>(device, path);
		}

		virtual void *Get()
		{
			return _asset.get();
		}
	};
}