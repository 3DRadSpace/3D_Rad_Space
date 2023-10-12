#pragma once
#include <Engine3DRadSpace/Graphics/ShaderPipeline.hpp>

class PickingShader : public Engine3DRadSpace::Graphics::Shaders::ShaderPipeline
{
	class VertexShader : public Engine3DRadSpace::Graphics::IVertexShader
	{
		Engine3DRadSpace::Graphics::InputLayoutElement elem[1];
	public:
		VertexShader(Engine3DRadSpace::GraphicsDevice* device);

		std::span<Engine3DRadSpace::Graphics::InputLayoutElement> InputLayout() override;
	};

	static inline Engine3DRadSpace::Graphics::InputLayoutElement elements[] = { Engine3DRadSpace::Graphics::InputLayoutElement::Position_Vec4 };

	class PixelShader : public Engine3DRadSpace::Graphics::IPixelShader
	{
	public:
		PixelShader(Engine3DRadSpace::GraphicsDevice* device);
	};

public: 
	PickingShader(Engine3DRadSpace::GraphicsDevice* device);
};