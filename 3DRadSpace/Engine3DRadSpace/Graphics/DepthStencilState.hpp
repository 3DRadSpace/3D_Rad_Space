#pragma once

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

	struct DepthStencilState
	{
		bool EnableDepthCheck;
		DepthWriteMask Mask;
		ComparisonFunction Function;

		bool EnableStencilCheck;
		uint8_t ReadMask;
		uint8_t WriteMask;
		struct Operation
		{
			StencilOperation StencilFail;
			StencilOperation DepthFail;
			StencilOperation PassOp;
			StencilOperation Function;
		} FrontFace, BackFace;
	};
}