#pragma once
#include "../ModelMeshPart.hpp"
#include "IRenderingEffect.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	class DLLEXPORT IRenderer
	{
	protected:
		GraphicsDevice* _device;
		std::vector<std::unique_ptr<IRenderingEffect>> _effects;

		IRenderer(GraphicsDevice* device);
	public:
		IRenderer(IRenderer&) = delete;
		IRenderer& operator=(IRenderer&) = delete;

		IRenderer(IRenderer&&) = default;
		IRenderer& operator=(IRenderer&&) = default;

		virtual void Begin() = 0;
		virtual void Draw(ModelMeshPart* part);
		virtual void Draw(VertexBuffer* vertices, IndexBuffer* indices);
		virtual void End() = 0;

		virtual ~IRenderer() = default;
	};
}