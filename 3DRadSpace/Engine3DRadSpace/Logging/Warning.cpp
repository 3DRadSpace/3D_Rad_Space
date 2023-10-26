#include "Warning.hpp"
#include <fstream>

using namespace Engine3DRadSpace::Logging;

Warning::Warning(const int32_t code,const int severity) : 
	Details(std::format("Warning code {} severity {}",code,severity)),
	Code(code),
	Severity(severity),
	Extra(nullptr)
{
}

Warning::Warning(const int32_t code, const char *details,const int severity, const void *extra) :
	Details(details),
	Code(code),
	Severity(severity),
	Extra(nullptr)
{
}

void Engine3DRadSpace::Logging::SetLastWarning(const Warning &warning)
{
	WarningHandler(warning);
}

void Engine3DRadSpace::Logging::DefaultWarningHandler(const Warning &warning)
{
	std::fstream file("Warnings.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	file <<"[WARNING]"<< warning.Details << " Code " << warning.Code << " Severity " << warning.Severity << std::endl; //new line + flush
	file.close();
}
FuncWarningHandler Engine3DRadSpace::Logging::WarningHandler = DefaultWarningHandler;
