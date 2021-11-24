#pragma once
#include "Globals.h"

#ifdef __DIRECTXVER

#include <d3d11.h>

namespace Engine3DRadSpace
{
	enum class RasterizerFillMode
	{
		FillWireframe = 2,
		FillSolid = 3
	};

	enum class RasterizerCullMode
	{
		None = 1,
		FrontFaces = 2,
		BackFaces = 3
	};

	struct RasterizerStateDesc
	{
		RasterizerFillMode FillMode;
		RasterizerCullMode CullMode;
		int FrontCounterClockwise;
		int DepthBias;
		float DepthBiasClamp;
		float SlopeScaledDepthBias;
		int DepthClipEnable;
		int ScissorEnable;
		int MultisampleEnable;
		int AntialiasedLineEnable;
	};

	class DLLEXPORT RasterizerState
	{
		ID3D11RasterizerState* _rasterizerState;
	public:
		RasterizerState(ID3D11Device* device);

		RasterizerState(ID3D11Device* device, const RasterizerStateDesc& desc);

		void SetRasterizerState(ID3D11DeviceContext* context);

		~RasterizerState();
	};
}
#endif

