#pragma once
#include "Font.hpp"
#include "FontShader.hpp"

namespace Engine3DRadSpace::Graphics::Fonts
{
	class DLLEXPORT FontRenderer
	{
		std::unique_ptr<FontShader> _shader;
		std::unique_ptr<SamplerState> _samplerState;

		GraphicsDevice* _device;
	public:
		FontRenderer(GraphicsDevice* device);

		FontRenderer(FontRenderer&) = delete;
		FontRenderer(FontRenderer&&) = delete;

		FontRenderer& operator=(FontRenderer&) = delete;
		FontRenderer& operator=(FontRenderer&&) = delete;

		void Render(Font& font, char chr);
	};
}