#pragma once
#include "Vector3.hpp"
#include "Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct VertexPosition
	{
		Vector3 Position;
	};

	struct UnspecifiedVertexDecl : VertexPosition
	{
		virtual void dummy() = 0;
	};

	struct VertexPositionColor : VertexPosition
	{
		Color Color;
	};

	struct VertexPositionNormalColor
	{
		Vector3 Normal;
		Color Color;
	};

	template <typename T>
	concept VertexDecl = std::is_base_of_v<VertexPosition, T>;
}