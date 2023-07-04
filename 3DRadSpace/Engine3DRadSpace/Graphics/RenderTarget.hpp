#pragma once
#include "Texture2D.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT RenderTarget : public Texture2D
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTarget;
#endif
	public:
		RenderTarget(GraphicsDevice *device);
		RenderTarget(GraphicsDevice *device, unsigned x, unsigned y);

		~RenderTarget() = default;

		friend class Engine3DRadSpace::GraphicsDevice;
	};
}

