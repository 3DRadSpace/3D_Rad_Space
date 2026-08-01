#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct E3DRSP_LOGGING_EXPORT Warning
	{
		const std::string Details;
		int32_t Code;
		int Severity;
		const void *Extra;

		Warning(const int32_t code, const int severity);
		Warning(const int32_t code, const std::string& details, const int severity, const void* extra = nullptr);
	};

	typedef void (*FuncWarningHandler)(const Warning& warning);
	extern FuncWarningHandler WarningHandler;

	inline void E3DRSP_LOGGING_EXPORT PrintWarning(const Warning &warning);
	inline void E3DRSP_LOGGING_EXPORT PrintWarning(const std::string &warning_text);
	inline void E3DRSP_LOGGING_EXPORT DefaultWarningHandler(const Warning &warning);
}
 