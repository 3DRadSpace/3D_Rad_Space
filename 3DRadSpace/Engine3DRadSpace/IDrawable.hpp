#pragma once
#include "GraphicsDevice.hpp"

namespace Engine3DRadSpace
{
	class IDrawable
	{
	public:
		virtual void Draw(GraphicsDevice* device, float dt) = 0;
		inline virtual ~IDrawable()
		{
		}
	};
}
