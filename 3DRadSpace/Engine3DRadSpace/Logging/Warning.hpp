#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct DLLEXPORT Warning
	{
		const std::string Details;
		int32_t Code;
		int Severity;
		const void *Extra;

		Warning(const int32_t code, const int severity);
		Warning(const int32_t code, const char *details,const int severity, const void *extra = nullptr);
	};

	typedef void (*FuncWarningHandler)(const Warning& warning);
	extern FuncWarningHandler WarningHandler;

	void DLLEXPORT SetLastWarning(const Warning &warning);
	void DLLEXPORT DefaultWarningHandler(const Warning &warning);
}
