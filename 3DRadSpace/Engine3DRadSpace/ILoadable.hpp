#pragma once
#include "Content/ContentManager.hpp"

namespace Engine3DRadSpace
{
	class ILoadable
	{
	public:
		virtual void Load(Content::ContentManager *content) = 0;
		virtual ~ILoadable() = default;
	};
}