#pragma once
#include "Asset.hpp"
#include "AssetReference.hpp"

namespace Engine3DRadSpace::Content
{
	class DLLEXPORT ContentManager
	{
		unsigned _lastID;
		GraphicsDevice* _device;
		std::vector<std::unique_ptr<IAsset>> _resources;
	public:
		ContentManager(GraphicsDevice *device);

		ContentManager(ContentManager &) = delete;
		ContentManager(ContentManager &&) noexcept = default;

		ContentManager &operator = (ContentManager &) = delete;
		ContentManager &operator = (ContentManager &&) noexcept = default;

		template<AssetType T>
		T *Load(const std::string &path, AssetReference<T> *ref = nullptr)
		{
			auto r = std::make_unique<Asset<T>>(_device, path);
			r->_id = _lastID++;

			for(auto &asset : _resources)
			{
				if(asset && asset->Path == path)
				{
					if(ref) *ref = AssetReference<T>(r->ID());
					return static_cast<T *>(asset->Get());
				}
			}

			unsigned int cID = r->ID();
			T* assetPtr = static_cast<T *>(r->Get());
			_resources.push_back(std::move(r));

			if(ref) *ref = AssetReference<T>(cID);
			return assetPtr;
		}

		template<AssetType T>
		void RemoveAsset(const T *asset)
		{
			for(size_t i = 0; i < _resources.size(); i++)
			{
				if(_resources[i].get() == asset)
				{
					_resources.erase(_resources.begin() + i);
					break;
				}
			}
		}

		template<AssetType T>
		IAsset *operator[](AssetReference<T> ref)
		{
			return _resources[ref.ID].get();
		}

		void RemoveAsset(const std::string &name);
		void RemoveAsset(unsigned id);
	};
}