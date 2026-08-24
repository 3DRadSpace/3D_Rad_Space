#pragma once
#include "IScript.hpp"
#include "CompilationResults.hpp"

namespace Engine3DRadSpace::Scripting
{
	/// <summary>
	/// Compiles scripts.
	/// </summary>
	class E3DRSP_SCRIPTING_EXPORT IScriptBuilder
	{
	protected:
		IScriptBuilder() = default;
	public:
		/// <summary>
		/// Returns an identifier of the language this builder supports. Usually the language name.
		/// </summary>
		/// <returns></returns>
		virtual const char* Language() const = 0;
		/// <summary>
		/// Is the builder not busy?
		/// </summary>
		/// <returns>true if available</returns>
		virtual bool IsAvailable() const = 0;

		using CompileReturn = std::pair<IScript*, CompilationResults>;
		/// <summary>
		/// Compiles a script from the given path and entry class.
		/// </summary>
		/// <param name="scriptPath">Script path in the filesystem.</param>
		/// <param name="entryClass">Entry class name</param>
		/// <returns></returns>
		virtual CompileReturn Compile(const char* scriptPath, const char* entryClass) = 0;

		virtual ~IScriptBuilder() = default;
	};
}