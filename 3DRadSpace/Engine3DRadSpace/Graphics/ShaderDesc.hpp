#pragma once
#include "../Core/Libs.hpp"
#include "ShaderType.hpp"
#include "ShaderFeatureLevel.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Shader description base polymorphic type.
	/// </summary>
	struct E3DRSP_GRAPHICS_EXPORT ShaderDesc
	{
	protected:
		/// <summary>
		/// Constructs an incomplete shader description
		/// </summary>
		/// <param name="EntryPoint">Entry point function name</param>
		/// <param name="type">Shader type</param>
		/// <param name="FeatureLevel">Shader feature level</param>
		ShaderDesc(
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);
	public:
		/// <summary>
		/// Entry point function name
		/// </summary>
		std::string EntryPoint;
		/// <summary>
		/// Shader type (fragment, vertex, etc.)
		/// </summary>
		ShaderType Type;
		/// <summary>
		/// Shader feature level
		/// </summary>
		ShaderFeatureLevel FeatureLevel;
	
		virtual ~ShaderDesc() = default;
	};

	struct E3DRSP_GRAPHICS_EXPORT ShaderDescFile : public ShaderDesc
	{
		/// <summary>
		/// Creates a shader description from a file path.
		/// </summary>
		/// <param name="FilePath">Path to the shader file(HLSL)</param>
		/// <param name="EntryPoint">Entry point function name</param>
		/// <param name="type">Shader type (fragment, vertex, etc.)</param>
		/// <param name="FeatureLevel">Shader feature level</param>
		ShaderDescFile(
			std::filesystem::path FilePath,
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);

		/// <summary>
		/// Path to the shader file(HLSL)
		/// </summary>
		std::filesystem::path FilePath;

		~ShaderDescFile() override = default;
	};

	struct E3DRSP_GRAPHICS_EXPORT ShaderDescSource : public ShaderDesc
	{
		/// <summary>
		/// Creates a shader description from a source code string.
		/// </summary>
		/// <param name="SourceCode">Shader source code (HLSL)</param>
		/// <param name="EntryPoint">Entry point function name</param>
		/// <param name="type">Shader type (fragment, vertex, etc.)</param>
		/// <param name="FeatureLevel">Shader feature level</param>
		ShaderDescSource(
			const std::string& SourceCode,
			const std::string& EntryPoint,
			ShaderType type,
			ShaderFeatureLevel FeatureLevel = ShaderFeatureLevel::DX_V4
		);

		/// <summary>
		///	Source code of the shader (HLSL)
		/// </summary>
		std::string SourceCode;

		~ShaderDescSource() override = default;
	};
}