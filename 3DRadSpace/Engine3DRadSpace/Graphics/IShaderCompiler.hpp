#pragma once
#include "ShaderCompilationResult.hpp"
#include "ShaderDesc.hpp"
#include "EffectManager.hpp"

namespace Engine3DRadSpace::Graphics
{
	class Effect;
	class IShader;

	/// <summary>
	/// Represents a interface for shader compilation.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IShaderCompiler
	{
	protected:
		IShaderCompiler();

		IShaderCompiler(const IShaderCompiler&) = delete;
		IShaderCompiler& operator=(const IShaderCompiler&) = delete;

		IShaderCompiler(IShaderCompiler&&) noexcept = default;
		IShaderCompiler& operator=(IShaderCompiler&&) noexcept = default;

		std::unique_ptr<EffectManager> _manager;
	public:
		using CompileOutput = std::pair<IShader*, ShaderCompilationResult>;
		using EffectCompileOutput = std::pair<Effect*, ShaderCompilationResult>;

		/// <summary>
		/// Compiles an shader based on the provided description.
		/// </summary>
		/// <param name="desc">Shader description.</param>
		/// <returns>A pair containing the compiled shader and the compilation result.</returns>
		virtual [[nodiscard]] CompileOutput Compile(const ShaderDesc* desc) = 0;
		/// <summary>
		/// Compiles an effect based on the provided shader descriptions.
		/// </summary>
		/// <param name="descs">A span of shader descriptions.</param>
		/// <returns>A pair containing the compiled effect and the compilation result.</returns>
		virtual [[nodiscard]] EffectCompileOutput CompileEffect(std::span<ShaderDesc*> descs) = 0;

		virtual ~IShaderCompiler() = default;
	};
}