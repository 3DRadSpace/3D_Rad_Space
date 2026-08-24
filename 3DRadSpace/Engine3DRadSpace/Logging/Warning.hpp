#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	/// <summary>
	/// Represents a warning in the logging system.
	/// </summary>
	struct E3DRSP_LOGGING_EXPORT Warning
	{
		/// <summary>
		/// Warning text. 
		/// </summary>
		std::string Details;
		/// <summary>
		/// Code for the warning, for example a HRESULT.
		/// </summary>
		int32_t Code;
		/// <summary>
		/// Code for severity.
		/// </summary>
		int Severity;
		/// <summary>
		/// Pointer to any extra data associated with this warning.
		/// </summary>
		const void *Extra;

		Warning(const int32_t code, const int severity);
		Warning(const int32_t code, const std::string& details, const int severity, const void* extra = nullptr);
	};

	/// <summary>
	/// Warning handler function type.
	/// </summary>
	typedef void (*FuncWarningHandler)(const Warning& warning);
	/// <summary>
	///	Current warning handler function.
	/// </summary>
	extern FuncWarningHandler WarningHandler;

	/// <summary>
	/// Submits an warning message to the logging system.
	/// </summary>
	/// <param name="warning">Warning instance</param>
	inline void E3DRSP_LOGGING_EXPORT PrintWarning(const Warning &warning);
	/// <summary>
	/// Submits an warning message to the logging system.
	/// </summary>
	/// <param name="warning_text">Warning text</param>
	inline void E3DRSP_LOGGING_EXPORT PrintWarning(const std::string &warning_text);
	/// <summary>
	/// Default warning handler function.
	/// </summary>
	/// <param name="warning">Warning instance</param>
	inline void E3DRSP_LOGGING_EXPORT DefaultWarningHandler(const Warning &warning);
}
 