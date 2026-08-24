#pragma once
#include "../IShaderCompiler.hpp"

namespace Engine3DRadSpace::Graphics::Null
{
    class GraphicsDevice;

	class E3DRSP_GRAPHICS_EXPORT ShaderCompiler final : public IShaderCompiler
	{
    public:
        explicit ShaderCompiler(GraphicsDevice* device);

        ShaderCompiler(const ShaderCompiler&) = delete;
        ShaderCompiler(ShaderCompiler&&) = delete;

        ShaderCompiler& operator=(const ShaderCompiler&) = delete;
        ShaderCompiler& operator=(ShaderCompiler&&) = delete;

        [[nodiscard]] CompileOutput Compile(const ShaderDesc* desc) override;
        [[nodiscard]] EffectCompileOutput CompileEffect(std::span<ShaderDesc*> descs) override;

        ~ShaderCompiler() override = default;
	};
}