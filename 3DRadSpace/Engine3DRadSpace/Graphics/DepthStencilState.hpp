#pragma once
#include "../GraphicsDevice.hpp"

namespace Engine3DRadSpace::Graphics
{
	enum class DepthWriteMask
	{
		Zero = 0,
		All = 1
	};

	enum class ComparisonFunction
	{
		Never = 1,
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always,
	};

	enum class StencilOperation
	{
		Keep = 1,
		Zero = 2,
		Replace = 3,
		IncrementClamp = 4,
		DecrementClamp = 5,
		Invert = 6,
		IncrementWrap = 7,
		DecrementWrap = 8
	};

	struct FaceOperation
	{
		StencilOperation StencilFail;
		StencilOperation DepthFail;
		StencilOperation PassOp;
		ComparisonFunction Function;
	};

	class DLLEXPORT DepthStencilState
	{
#ifdef _DX11
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _state;
#endif
	public:
		DepthStencilState(GraphicsDevice *device);

		DepthStencilState( GraphicsDevice *device, bool EnableDepth, DepthWriteMask Mask, ComparisonFunction Function, bool EnableStencil,
			uint8_t ReadMask, uint8_t WriteMask, FaceOperation FrontFace, FaceOperation BackFace);

		DepthStencilState(DepthStencilState &) = delete;
		DepthStencilState(DepthStencilState &&state) noexcept = default;

		DepthStencilState& operator=(DepthStencilState &) = delete;
		DepthStencilState &operator=(DepthStencilState &&state) noexcept = default;

		static DepthStencilState DepthDefault(GraphicsDevice* device);
		static DepthStencilState DepthNone(GraphicsDevice *device);
		static DepthStencilState DepthRead(GraphicsDevice *device);

		static DepthStencilState DepthReverseZ(GraphicsDevice *device);
		static DepthStencilState DepthReadReverseZ(GraphicsDevice *device);

		~DepthStencilState() = default;

		friend class GraphicsDevice;
	};
}