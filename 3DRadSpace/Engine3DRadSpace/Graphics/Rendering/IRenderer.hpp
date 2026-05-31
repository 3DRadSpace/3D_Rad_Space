#pragma once
#include "../ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a rendering pipeline that allows multiple rendering effects.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT IRenderer
	{
	protected:
		IGraphicsDevice* _device;

		IRenderer(IGraphicsDevice* device);
	public:
		IRenderer(const IRenderer&) = delete;
		IRenderer& operator=(const IRenderer&) = delete;

		IRenderer(IRenderer&&) noexcept = default;
		IRenderer& operator=(IRenderer&&) noexcept = default;

		/// <summary>
		/// Prepares the graphics pipeline for this effect.
		/// </summary>
		virtual void Begin() = 0;
		/// <summary>
		/// Submits a mesh part to this effect.
		/// </summary>
		/// <param name="part">Mesh</param>
		virtual void Draw(ModelMeshPart* part);
		/// <summary>
		/// Submits a mesh made of a index and vertex buffer to this effect.
		/// </summary>
		/// <param name="vertices">Vertices</param>
		/// <param name="indices">Incides</param>
		virtual void Draw(IVertexBuffer* vertices, IIndexBuffer* indices, Effect* effect);
		/// <summary>
		/// Restores the previous states, and depending on the effect, draws all submited meshes. (Unless meshes are not batched).
		/// </summary>
		virtual void End() = 0;

		IGraphicsDevice* GetDevice() const noexcept;

		virtual ~IRenderer() = default;
	};
}