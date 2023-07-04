#pragma once
#include "Content/ContentManager.hpp"

namespace Engine3DRadSpace
{
	class DLLEXPORT ILoadable
	{
	public:
		virtual void Load(Content::ContentManager *content) = 0;
		virtual ~ILoadable() = default;
	};
}