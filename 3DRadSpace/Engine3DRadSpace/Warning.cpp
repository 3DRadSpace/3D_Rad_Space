#include "Warning.hpp"
#include <fstream>

Engine3DRadSpace::Logging::Warning::Warning(int32_t code, int severity) : 
	Details(std::format("Warning code {} severity {}",code,severity).c_str()),
	Code(code),
	Severity(severity)
{
}

Engine3DRadSpace::Logging::Warning::Warning(int32_t code, const char *details, int severity, const void *extra) :
	Details(details),
	Code(code),
	Severity(severity)
{
}

void Engine3DRadSpace::Logging::SetLastWarning(const Warning &warning)
{
	Engine3DRadSpace::Logging::WarningHandler(warning);
}

void Engine3DRadSpace::Logging::DefaultWarningHandler(const Warning &warning)
{
	std::fstream file("Warnings.log", std::ios::app | std::ios::out | std::ios::ate); //create a file stream for writing, with append and seek end flags
	file << warning.Details << " Code " << warning.Code << " Severity " << warning.Severity;
	file.close();
}
Engine3DRadSpace::Logging::FuncWarningHandler Engine3DRadSpace::Logging::WarningHandler = Engine3DRadSpace::Logging::DefaultWarningHandler;
