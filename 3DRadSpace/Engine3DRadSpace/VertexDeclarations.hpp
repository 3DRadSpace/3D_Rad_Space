#pragma once
#include "Vector3.hpp"
#include "Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	struct VertexPosition
	{
		Math::Vector3 Position;
	};

	struct UnspecifiedVertexDecl
	{
		Math::Vector3 Position;
		virtual void dummy() = 0;
	};

	struct VertexPositionColor
	{
		Math::Vector3 Position;
		Color Color;
	};

	struct VertexPositionNormalColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Color Color;
	};

	template <typename V>
	concept VertexDecl = requires(V v)
	{
		v.Position = Math::Vector3::Zero();
	};
}