#pragma once
#include "../ModelMeshPart.hpp"
#include "RenderPassType.hpp"
#include "MaterialDescriptor.hpp"

namespace Engine3DRadSpace
{
	class IGame;
}

namespace Engine3DRadSpace::Graphics::Rendering
{
	class RenderingManager;

	/// <summary>
	/// Represents a rendering pipeline that allows multiple rendering effects.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT IRenderer
	{
	protected:
		IGraphicsDevice* _device;
		IGraphicsCommandList* _context;
		RenderingManager* _owner;

		IRenderer(RenderingManager* owner);

		IRenderer(const IRenderer&) = delete;
		IRenderer& operator=(const IRenderer&) = delete;

		IRenderer(IRenderer&&) noexcept = default;
		IRenderer& operator=(IRenderer&&) noexcept = default;
	public:
		/// <summary>
		/// Prepares the graphics pipeline for this effect.
		/// </summary>
		virtual void Begin() = 0;
		/// <summary>
		/// Submits a mesh part to this effect.
		/// </summary>
		/// <param name="part">Mesh</param>
		virtual void Draw(ModelMeshPart* part, const MaterialDescriptor* material) = 0;
		/// <summary>
		/// Draws all supported mesh parts.
		/// </summary>
		virtual void End() = 0;

		/// <summary>
		/// Determines whether the specified render pass type is supported by this renderer.
		/// </summary>
		/// <param name="passType">The render pass type to check.</param>
		/// <returns>True if the render pass type is supported; otherwise, false.</returns>
		virtual bool IsRenderPassTypeSupported(RenderPassType passType) const noexcept = 0;

		virtual ~IRenderer() = default;

		friend class RenderingManager;
	};
}