#pragma once
#include "..\..\Graphics\ShaderPipeline.hpp"
#include "..\..\Math\Matrix.hpp"

namespace Engine3DRadSpace::Algorithms::Picking
{
	class DLLEXPORT PickingShader : public Graphics::Shaders::ShaderPipeline
	{
		class VertexShader : public Graphics::IVertexShader
		{
			static inline Graphics::InputLayoutElement _elements[] = {Graphics::InputLayoutElement::Position_Vec4 };
		public:
			explicit VertexShader(GraphicsDevice* device);

			std::span<Graphics::InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public Graphics::IPixelShader
		{
		public:
			explicit PixelShader(GraphicsDevice* device);
		};

	public:
		struct alignas(16) Data
		{
			/// <summary>
			/// Model-View-Projection transformation matrix.
			/// </summary>
			Math::Matrix MVP;
			unsigned int ObjectID;
		};

		explicit PickingShader(GraphicsDevice* device);

		void SetData(const Data& d);
	};
}