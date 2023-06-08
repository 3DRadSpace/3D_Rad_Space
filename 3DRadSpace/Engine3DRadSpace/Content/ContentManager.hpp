#pragma once
#include "Asset.hpp"
#include "AssetReference.hpp"

namespace Engine3DRadSpace::Content
{
	class ContentManager
	{
		unsigned _lastID;
		GraphicsDevice* _device;
		std::vector<std::unique_ptr<IAsset>> _resources;
	public:
		ContentManager(GraphicsDevice *device);

		template<AssetType T>
		std::pair<T *, AssetReference<T>> LoadForEditor(const std::string &path)
		{
			auto r = std::make_unique<Asset<T>>(_device, path);
			r->ID = _lastID++;

			for(auto &asset : _resources)
			{
				if(asset->Path == path)
					return std::make_pair(asset->Get(), asset->ID());
			}

			_resources.push_back(r);
			return std::make_pair(r.get(), AssetReference(r->ID));
		}

		template<AssetType T>
		T *Load(const std::string &path)
		{
			auto asset = std::make_unique<Asset<T>>(_device, path);
			
			T *retPtr = static_cast<T *>(asset->Get());
			
			asset->_id = _lastID++;
			_resources.push_back(std::move(asset));

			return retPtr;
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