#pragma once
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"
#include "../Math/Color.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents the base vertex declaration only with a 3D position attribute.
	/// </summary>
	struct VertexPosition
	{
		Math::Vector3 Position;
	};

	/// <summary>
	/// Represents a 3D vertex declaration a color attribute.
	/// </summary>
	struct VertexPositionColor
	{
		Math::Vector3 Position;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with a 2D texture coordinate attribute.
	/// </summary>
	struct VertexPositionUV
	{
		Math::Vector3 Position;
		Math::Vector2 UV;
	};

	/// <summary>
	/// Represents a 2D vertex declaration with a 2D texture coordinate attribute.
	/// </summary>
	struct VertexPointUV
	{
		Math::Vector2 Position;
		Math::Vector2 UV;
	};

	/// <summary>
	///	Represents a 3D vertex declaration with a 3D normal attribute, and a color attribute.
	/// </summary>
	struct VertexPositionNormalColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with a 3D normal attribute, and a 2D texture coordinate attribute.
	/// </summary>
	struct VertexPositionNormalUV
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector2 UV;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with a 3D normal attribute, a 2D texture coordinate attribute, and a color attribute.
	/// </summary>
	struct VertexPositionNormalUVColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector2 UV;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with normal and tangent space.
	/// </summary>
	struct VertexPositionNormalBitangent
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with normal, tangent space, and color.
	/// </summary>
	struct VertexPositionNormalBitangentColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with normal, tangent space, and texture coordinates.
	/// </summary>
	struct VertexPositionNormalBitangentUVColor
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Vector2 UV;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a 3D vertex declaration with normal, tangent space, and texture coordinates.
	/// </summary>
	struct VertexPositionNormalBitangentUV
	{
		Math::Vector3 Position;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
		Math::Vector3 Bitangent;
		Math::Vector2 UV;
	};

	/// <summary>
	/// Represents a 2D vertex declaration with a 2D texture coordinate attribute, and a color attribute.
	/// </summary>
	struct VertexPointUVColor
	{
		Math::Vector2 Position;
		Math::Vector2 UV;
		Math::Color Color;
	};

	/// <summary>
	/// Represents a concept for a vertex declaration.
	/// </summary>
	template <typename V>
	concept VertexDecl = requires(V v)
	{
		v.Position = Math::Vector4::Zero();
	} || requires(V v)
	{
		v.Position = Math::Vector3::Zero();
	} || requires(V v)
	{
		v.Position = Math::Vector2::Zero();
	};
}