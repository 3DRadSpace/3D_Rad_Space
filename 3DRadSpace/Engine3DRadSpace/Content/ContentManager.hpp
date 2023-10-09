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
		T *Load(const std::string &path, AssetReference<T> *ref = nullptr);

		template<AssetType T>
		void Reload(AssetReference<T> ref);

		template<AssetType T>
		void Reload(const std::string &name);

		template<AssetType T>
		void Reload(unsigned id);

		template<AssetType T>
		void RemoveAsset(const T *asset);

		template<AssetType T>
		IAsset *operator[](AssetReference<T> ref);

		std::vector<std::unique_ptr<IAsset>>::iterator begin();
		std::vector<std::unique_ptr<IAsset>>::iterator end();

		void RemoveAsset(const std::string &name);
		void RemoveAsset(unsigned id);

		GraphicsDevice* GetDevice();
	};










	///
	///										IMPLEMENTATION FOR ContentManager TEMPLATE METHODS
	/// ___________________________________________________________________________________________________________________________________________
	/// 

	template<AssetType T>
	inline T *ContentManager::Load(const std::string &path, AssetReference<T> *ref)
	{
		//Find existing resource
		for(auto &asset : _resources)
		{
			if(asset && asset->Path == path)
			{
				if(ref) *ref = AssetReference<T>(asset->ID());
				return static_cast<T *>(asset->Get());
			}
		}

		//Else create a new one
		auto r = std::make_unique<Asset<T>>(_device, path);
		r->_id = _lastID++;

		unsigned int cID = r->ID();
		T *assetPtr = static_cast<T *>(r->Get());
		_resources.push_back(std::move(r));

		if(ref) *ref = AssetReference<T>(cID);
		return assetPtr;
	}

	template<AssetType T>
	inline void ContentManager::Reload(AssetReference<T> ref)
	{
		auto path = _resources[ref.ID]->Path;

		_resources[ref.ID].reset(new Asset<T>(_device, path));
	}

	template<AssetType T>
	inline void ContentManager::Reload(const std::string &name)
	{
		auto f = std::find(_resources.begin(), _resources.end(),
			[name](std::unique_ptr<IAsset> &asset) -> bool
		{
			return asset->Name == name;
		});

		if(f != _resources.end())
		{
			f->reset(new Asset<T>(_device, f->get()->Path));
		}
	}

	template<AssetType T>
	inline void ContentManager::Reload(unsigned id)
	{
		auto path = _resources[id]->Path;
		_resources[id].reset(new Asset<T>(_device, path));
	}

	template<AssetType T>
	inline void ContentManager::RemoveAsset(const T *asset)
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
	inline IAsset *ContentManager::operator[](AssetReference<T> ref)
	{
		return _resources[ref.ID].get();
	}
}