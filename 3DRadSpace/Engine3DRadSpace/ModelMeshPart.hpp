#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ModelMeshPart
	{
	public:
		std::unique_ptr<Engine3DRadSpace::Graphics::IndexBuffer> IndexBuffer;
		std::unique_ptr<Engine3DRadSpace::Graphics::VertexBuffer> VertexBuffer;

		void Draw();
	};
}

