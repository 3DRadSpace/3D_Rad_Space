#pragma once
#include "Graphics/SpriteBatch.hpp"

namespace Engine3DRadSpace
{
	class IDrawable2D
	{
	public:
		virtual void Draw(Graphics::SpriteBatch* spriteBatch, double dt) = 0;

		~IDrawable2D() = default;
	};
}