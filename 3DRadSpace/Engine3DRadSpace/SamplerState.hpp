#pragma once
#include "GraphicsDevice.hpp"

namespace Engine3DRadSpace
{
	enum TextureAddressMode
	{
		Wrap = 1,
		Mirror = 2,
		Clamp = 3,
		Border = 4,
		MirrorOnce = 5
	};

	class SamplerState
	{
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	public:
		SamplerState(GraphicsDevice* device);

		friend class Graphics::IShader;
	};
}

