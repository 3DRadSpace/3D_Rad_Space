#pragma once
#include "../../Core/IDrawable3D.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../ModelMeshPart.hpp"
#include "../Effect.hpp"
#include "../VertexDeclarations.hpp"

namespace Engine3DRadSpace::Graphics::Primitives
{
	/// <summary>
	/// Base class for vertex coloured primitive shapes.
	/// </summary>
	/// <remarks>
	/// IPrimitive is the base for vertex coloured, trivial meshes without normals, UV coordinates, bitangents, etc...
	/// Primitives are meant to wrap a vertex Position Color declared buffer and a index buffer.
	/// </remarks>
	class E3DRSP_GRAPHICS_PRIMITIVES_EXPORT IPrimitive : public IDrawable3D
	{
	protected:
		IPrimitive(IGraphicsDevice* device, std::nullptr_t nullShader);
		IPrimitive(IGraphicsDevice* device);

		IPrimitive(const IPrimitive&) noexcept = default;
		IPrimitive& operator=(const IPrimitive&) noexcept = default;

		IPrimitive(IPrimitive&&) noexcept = default;
		IPrimitive& operator=(IPrimitive&&) noexcept = default;

		IGraphicsDevice* _device;
		std::unique_ptr<IVertexBuffer> _vertices;
		std::unique_ptr<IIndexBuffer> _indices;

		Effect* _shader;

		virtual Math::Matrix4x4 _mvp() const noexcept;
	public:
		/// <summary>
		/// Camera view matrix.
		/// </summary>
		Math::Matrix4x4 View;
		/// <summary>
		/// Camera projection matrix.
		/// </summary>
		Math::Matrix4x4 Projection;
		/// <summary>
		/// World transform, composed usually of Scale, Rotation, Translation.
		/// </summary>
		Math::Matrix4x4 Transform;

		void Draw3D() override;

		~IPrimitive() override = default;
	};
}