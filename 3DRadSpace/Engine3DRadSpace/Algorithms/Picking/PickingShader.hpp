#pragma once
#include "..\..\Graphics\ShaderPipeline.hpp"
#include "..\..\Math\Matrix.hpp"

namespace Engine3DRadSpace::Algorithms::Picking
{
	class PickingShader : public Engine3DRadSpace::Graphics::Shaders::ShaderPipeline
	{
		class VertexShader : public Engine3DRadSpace::Graphics::IVertexShader
		{
			static inline Engine3DRadSpace::Graphics::InputLayoutElement _elements[] = { Engine3DRadSpace::Graphics::InputLayoutElement::Position_Vec4 };
		public:
			explicit VertexShader(Engine3DRadSpace::GraphicsDevice* device);

			std::span<Engine3DRadSpace::Graphics::InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public Engine3DRadSpace::Graphics::IPixelShader
		{
		public:
			explicit PixelShader(Engine3DRadSpace::GraphicsDevice* device);
		};

	public:
		struct alignas(16) Data
		{
			/// <summary>
			/// Model-View-Projection transformation matrix.
			/// </summary>
			Engine3DRadSpace::Math::Matrix MVP;
			unsigned int ObjectID;
		};

		explicit PickingShader(Engine3DRadSpace::GraphicsDevice* device);

		void SetData(const Data& d);
	};
}