#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Logging
{
	struct DLLEXPORT Warning
	{
		const char *Details;
		int32_t Code;
		int Severity;
		const void *Extra;

		Warning(int32_t code, int severity);
		Warning(int32_t code, const char *details, int severity, const void *extra = nullptr);
	};

	typedef void (*FuncWarningHandler)(const Warning& warning);
	extern FuncWarningHandler WarningHandler;

	void DLLEXPORT SetLastWarning(const Warning &warning);
	void DLLEXPORT DefaultWarningHandler(const Warning &warning);
}
