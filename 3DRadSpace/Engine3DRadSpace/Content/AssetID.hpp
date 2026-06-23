#pragma once
#include "IAsset.hpp"

namespace Engine3DRadSpace::Content
{
	/// <summary>
	/// Unsigned numerical identifier of an asset, paired with a template type.
	/// </summary>
	/// <typeparam name="T">T must be a AssetType - must inherit IAsset and be constructible from a factory class and a path.</typeparam>
	template<AssetType T>
	struct AssetID
	{
		/// <summary>
		/// Constructs an AssetID with an null identifier.
		/// </summary>
		AssetID() : ID(0) {};
		/// <summary>
		/// Constructs an AssetID with the specified identifier.
		/// </summary>
		/// <param name="id">Identifier of the asset.</param>
		AssetID(unsigned id) : ID(id) {};

		/// <summary>
		/// Underlying unsigned identifier of the asset.
		/// </summary>
		unsigned ID;

		/// <summary>
		/// Gets the underlying unsigned identifier of the asset.
		/// </summary>
		operator unsigned() const noexcept
		{
			return ID;
		}

		/// <summary>
		/// Type of the asset associated with this AssetID.
		/// </summary>
		using Type = T;
	};
}