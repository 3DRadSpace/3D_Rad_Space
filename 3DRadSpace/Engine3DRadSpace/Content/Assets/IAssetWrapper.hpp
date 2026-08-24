#pragma once
#include "../IAsset.hpp"

namespace Engine3DRadSpace::Content::Assets
{
	/// <summary>
	/// Internal Asset wrapper for an asset type.
	/// </summary>
	/// <typeparam name="T">Asset type</typeparam>
	template<typename T>
	class IAssetWrapper : public IAsset
	{
	protected:
		std::optional<T> _asset;

		/// <summary>
		/// Main constructor.
		/// </summary>
		/// <param name="asset">Asset instance. Ownership will be transferred to this</param>
		IAssetWrapper(T&& asset) noexcept : _asset(std::make_optional<T>(std::move(asset))) 
		{
		}
		
		/// <summary>
		/// Default constructor with an invalid state.
		/// </summary>
		IAssetWrapper() noexcept
		{
		}

	public:
		/// <summary>
		/// Returns an reference to the underlying asset.
		/// </summary>
		operator T& ()
		{
			return *_asset;
		}

		/// <summary>
		/// Returns an reference to the underlying asset.
		/// </summary>
		const T* Get() const
		{
			return _asset.operator->();
		}

		/// <summary>
		/// Returns an reference to the underlying asset.
		/// </summary>
		T* Get()
		{
			return _asset.operator->();
		}
		
		/// <summary>
		/// Returns an reference to the underlying asset.
		/// </summary>
		const T* operator->() const
		{
			return _asset.operator->();
		}

		/// <summary>
		/// Returns an reference to the underlying asset.
		/// </summary>
		T* operator->()
		{
			return _asset.operator->();
		}

		/// <summary>
		/// Does this have an underlying asset instance?
		/// </summary>
		/// <returns>True if there is an underlying asset instance, false otherwise</returns>
		bool HasValue() const noexcept
		{
			return _asset.has_value();
		}

	public:
		~IAssetWrapper() override = default;
	};
}