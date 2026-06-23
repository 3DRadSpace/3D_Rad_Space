#pragma once
#include "AssetID.hpp"
#include "../Core/IGame.hpp"
#include "../Core/AssetUUIDReader.hpp"

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// Manages the lifetimes of all loaded assets.
	/// </summary>
	class E3DRSP_CONTENT_EXPORT ContentManager : public IService
	{
		struct AssetEntry
		{
			template<AssetType T>
			AssetEntry(IService* service, const std::filesystem::path& path) :
				Path(path),
				Entry(std::unique_ptr<T>(static_cast<IAsset*>(new T(service, path)))),
				Type(Entry->GetUUID()),
				RTTI(typeid(T)),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			template<AssetType T>
			AssetEntry(std::unique_ptr<T>&& asset, const std::filesystem::path& path) :
				Entry(std::move(asset)),
				Path(path),
				Type(Entry->GetUUID()),
				RTTI(typeid(T)),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			AssetEntry(std::unique_ptr<IAsset>&& asset, const std::filesystem::path& path) :
				Entry(std::move(asset)),
				Path(path),
				Type(Entry->GetUUID()),
				RTTI(typeid(*Entry.get())),
				Name(std::filesystem::path(path).stem().string())
			{
			}

			explicit AssetEntry(std::nullptr_t a) : Type(), RTTI(typeid(void)) {};

			AssetEntry(AssetEntry&&) noexcept = default;
			AssetEntry& operator=(AssetEntry&&) noexcept = default;

			std::unique_ptr<Content::IAsset> Entry;
			std::filesystem::path Path;
			Reflection::UUID Type;
			std::type_index RTTI;
			size_t ID = 0;
			std::string Name;
		};

		class AssetFactory
		{
			struct TypeEntry
			{
				Reflection::UUID UUID;
				std::function<IAsset* (IService*, const std::filesystem::path&)> Ctor;
				IService* Service;
			};

			std::vector<TypeEntry> _types;
			std::unordered_map<std::type_index, IService*> _services;

			IGame* _owner; 
		public:
			AssetFactory(IGame* owner);

			template<AssetType T>
			std::unique_ptr<T> Create(const std::filesystem::path& path)
			{
				RegisterType<T>({});

				auto serviceType = Internal::AssetUUIDReader::GetInitializationService<T>({});

				return std::make_unique<T>(
					_services[serviceType],
					path
				);
			}

			template<AssetType T>
			bool RegisterType(Tag<T> dummy)
			{
				if (std::find_if(_types.begin(), _types.end(), [](const TypeEntry& t) -> bool
					{
						auto uuid = Internal::AssetUUIDReader::GetUUID<T>({});
						return uuid == t.UUID;
					}
				) != _types.end())
				{
					return false;
				}
				else
				{
					auto serviceType = Internal::AssetUUIDReader::GetInitializationService<T>({});

					_services[serviceType] = static_cast<IService*>(_owner->GetService(serviceType));

					_types.emplace_back(
						Internal::AssetUUIDReader::GetUUID<T>({}),
						[](IService* service, const std::filesystem::path& path) -> IAsset*
						{
							return static_cast<IAsset*>(new T(service, path));
						},
						_services[serviceType]
					);

					return true;
				}

			}

			IAsset* Create(const Reflection::UUID& uuid, const std::filesystem::path& path);

		} _factory;

		unsigned _lastID;
		std::vector<AssetEntry> _assets;
		IGame* _owner;
	public:
		/// <summary>
		/// Constructs an instance of ContentManager.
		/// </summary>
		/// <param name="owner">Owner of this ContentManager.</param>
		ContentManager(IGame* owner);

		ContentManager(const ContentManager &) = delete;
		ContentManager(ContentManager &&) noexcept = default;

		ContentManager &operator =(const ContentManager &) = delete;
		ContentManager &operator =(ContentManager &&) noexcept = default;

		/// <summary>
		/// Registers an type T into this ContentManager.
		/// </summary>
		/// <typeparam name="T">Type that must satisfy the AssetType concept</typeparam>
		/// <param name="dummy">Type dummy used for operator overloading</param>
		template<AssetType T>
		void RegisterType(Tag<T> dummy);

		/// <summary>
		/// Loads an asset of type T from the specified path.
		/// </summary>
		/// <typeparam name="T">Asset type.</typeparam>
		/// <param name="path">Path on disk to the asset.</param>
		/// <param name="refID">Optional reference ID to store the asset's ID.</param>
		/// <returns>Pointer to the loaded asset.</returns>
		template<AssetType T>
		T* Load(const std::filesystem::path& path, AssetID<T>* refID = nullptr);

		/// <summary>
		/// Loads an asset of type T with additional constructor parameters.
		/// </summary>
		/// <typeparam name="...Args">Extra type arguments</typeparam>
		/// <typeparam name="T">Asset type</typeparam>
		/// <param name="path">Path on disk to the asset.</param>
		/// <param name="refID">Optional reference ID to store the asset's ID.</param>
		/// <param name="...params">Additional constructor parameters.</param>
		/// <returns>Pointer to the loaded asset.</returns>
		template<AssetType T, typename ...Args>
		T* Load(const std::filesystem::path& path, AssetID<T>* refID, Args&& ...params);

		/// <summary>
		/// Type erased asset loading function.
		/// </summary>
		/// <param name="uuid">UUID of the asset type.</param>
		/// <param name="path">Path on disk to the asset.</param>
		/// <param name="refID">Optional reference ID to store the asset's ID.</param>
		/// <returns>Pointer to the loaded asset.</returns>
		IAsset* Load(const Reflection::UUID &uuid, const std::filesystem::path& path, unsigned* refID = nullptr);

		/// <summary>
		/// Reloads an asset by its reference ID.
		/// </summary>
		/// <param name="ref">Asset reference ID</param>
		void Reload(unsigned ref);

		/// <summary>
		/// Returns an pointer to the asset of type T associated with the given reference ID.
		/// </summary>
		/// <typeparam name="T">Asset type</typeparam>
		/// <param name="ref">Asset reference ID</param>
		/// <returns>Pointer to the asset of type T</returns>
		template<AssetType T>
		T *operator[](AssetID<T> ref);

		/// <summary>
		/// Returns the path an asset with the specified ID was loaded from.
		/// </summary>
		/// <param name="id">Asset ID</param>
		/// <returns>Path to the asset</returns>
		std::filesystem::path GetAssetPath(unsigned id) const noexcept;
		/// <summary>
		/// Returns the type UUID of the specified asset ID.
		/// </summary>
		/// <param name="id">Asset ID</param>
		/// <returns>Type UUID of the asset</returns>
		Reflection::UUID GetAssetType(unsigned id) const noexcept;

		/// <summary>
		/// Returns the name of the specified asset ID.
		/// </summary>
		/// <param name="id">Asset ID</param>
		/// <returns>Name of the asset</returns>
		std::string GetAssetName(unsigned id) const noexcept;

		std::vector<AssetEntry>::iterator begin();
		std::vector<AssetEntry>::iterator end();

		/// <summary>
		/// Frees an asset from the ContentManager by its ID.
		/// </summary>
		/// <param name="id">Asset ID</param>
		void RemoveAsset(unsigned id);
		/// <summary>
		/// Removes all assets from the ContentManager.
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the graphics device associated with this ContentManager.
		/// </summary>
		/// <returns>Pointer to the graphics device</returns>
		Graphics::IGraphicsDevice* GetDevice() const noexcept;
		/// <summary>
		/// Returns the number of loaded assets in the ContentManager.
		/// </summary>
		/// <returns>Number of loaded assets</returns>
		size_t Count() const noexcept;

		~ContentManager() override = default;
	};










	///
	///										IMPLEMENTATION FOR ContentManager TEMPLATE METHODS
	/// ___________________________________________________________________________________________________________________________________________
	/// 
	///


	template<AssetType T>
	inline T* ContentManager::Load(const std::filesystem::path& path, AssetID<T> *refID)
	{
		auto asset = _factory.Create<T>(path);
		auto ptr = asset.get();

		_assets.emplace_back(std::move(asset), path);
		_assets[_assets.size() - 1].ID = _assets.size() - 1;

		if (refID)
		{
			*refID = static_cast<unsigned>(_assets.size() - 1);
		}
		return ptr;
	}

	template<AssetType T, typename ...Args>
	inline T* ContentManager::Load(const std::filesystem::path& path, AssetID<T>* refID, Args && ...params)
	{
		auto asset = _factory.Create<T>(path, std::forward<Args>(params)...);
		auto ptr = asset.get();

		_assets.emplace_back(std::move(asset), path);
		_assets[_assets.size() - 1].ID = _assets.size() - 1;

		if (refID)
		{
			*refID = _assets.size() - 1;
		}
		return ptr;
	}

	template<AssetType T>
	inline T* ContentManager::operator[](AssetID<T> ref)
	{
		return dynamic_cast<T*>(_assets[ref].Entry.get());
	}

	template<AssetType T>
	inline void ContentManager::RegisterType(Tag<T> dummy)
	{
		_factory.RegisterType<T>({});
	}
}