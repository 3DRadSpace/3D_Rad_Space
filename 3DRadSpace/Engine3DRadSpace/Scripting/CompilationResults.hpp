#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Scripting
{
	/// <summary>
	/// Represents compilation results of a script.
	/// </summary>
	struct CompilationResults
	{
		/// <summary>
		/// True if the compilation was successful, false otherwise.
		/// </summary>
		bool Successful;
		/// <summary>
		/// C-Style string to the errors. Null if no errors.
		/// </summary>
		const char* Errors;
		/// <summary>
		/// C-Style string to the warnings. Null if no warnings.
		/// </summary>
		const char* Warnings;
		/// <summary>
		/// C-Style string to the messages. Null if no messages.
		/// </summary>
		const char* Messages;
	};
}