#pragma once
#include "../Effect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IRenderingEffect
	{
	protected:
		IRenderingEffect() = default;
		IRenderingEffect(IRenderingEffect&&) = default;

		IRenderingEffect& operator=(IRenderingEffect&&) = default;
	public:
		IRenderingEffect(IRenderingEffect&) = delete;
		IRenderingEffect& operator=(IRenderingEffect&) = delete;

		virtual void Apply() = 0;

		virtual ~IRenderingEffect() = default;
	};
}
