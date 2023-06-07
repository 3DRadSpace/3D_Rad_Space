#pragma once
#include "Asset.hpp"
#include "AssetReference.hpp"

namespace Engine3DRadSpace::Content
{
	class ContentManager
	{
		unsigned _lastID;
		std::unique_ptr<GraphicsDevice> _device;
		std::vector<std::unique_ptr<IAsset>> _resources;
	public:
		ContentManager(GraphicsDevice *device);

		template<AssetType T>
		std::pair<T*, AssetReference<T>> LoadForEditor(const std::string &path)
		{
			auto r = std::make_unique<Asset<T>>(_device, path);
			r->ID = _lastID++;
			_resources.push_back(r);

			return std::make_pair(r.get(), AssetReference(r->ID));
		}

		template<AssetType T>
		T *Load(const std::string &path)
		{
			auto r = std::make_unique<Asset<T>>(_device, path);
			r->ID = _lastID++;
			_resources.push_back(r);

			return r.get();
		}

		template<AssetType T>
		void RemoveAsset(const T *asset)
		{
			_resources.erase(std::remove(_resources.begin(), _resources.end(), asset), vec.end());
		}

		template<AssetType T>
		IAsset *operator[](AssetReference<T> ref)
		{
			return _resources[ref.id].get();
		}

		IAsset *operator[](unsigned id);

		void RemoveAsset(const std::string &name);
		void RemoveAsset(unsigned id);
	};
}