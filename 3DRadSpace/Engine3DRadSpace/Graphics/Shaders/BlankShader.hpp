#pragma once
#include "../ShaderPipeline.hpp"
#include "../../Math/Matrix.hpp"

namespace Engine3DRadSpace::Graphics::Shaders
{
	class BlankShader : public ShaderPipeline
	{
		class VertexShader : public IVertexShader
		{
		public:
			explicit VertexShader(GraphicsDevice* device);

			std::span<InputLayoutElement> InputLayout() override;
		};

		class PixelShader : public IPixelShader
		{
		public:
			explicit PixelShader(GraphicsDevice* device);
		};
		static inline InputLayoutElement elements[2] = { InputLayoutElement::Position_Vec3, InputLayoutElement::Color };

	public:
		explicit BlankShader(GraphicsDevice* device);

		/// <summary>
		/// Sets the linear transformation used to render the primitives.
		/// </summary>
		/// <param name="matrix">A MVP (model-view-projection) linear transformation is required.</param>
		void SetTransformation(const Math::Matrix &matrix);
	};
}