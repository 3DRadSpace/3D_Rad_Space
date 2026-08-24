#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Represents the result of a shader compilation process.
	/// </summary>
	struct ShaderCompilationResult
	{
		/// <summary>
		/// All warnings and errors that occurred during the compilation process.
		/// </summary>
		std::string Log;
		/// <summary>
		/// True if succeded, false otherwise.
		/// </summary>
		bool Succeded;
		/// <summary>
		/// Shader name/identifier.
		/// </summary>
		std::string Identifier;
	};
}