#pragma once
#include "IAsset.hpp"

namespace Engine3DRadSpace::Content
{
	template<AssetType T> 
	struct AssetReference
	{
		AssetReference() : ID(0) {}
		AssetReference(unsigned id) : ID(id) {}

		unsigned ID;
		
		operator unsigned()
		{ 
			return ID;
		}
	};
}