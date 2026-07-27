#include "Warning.h"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace::Logging;

void E3DRSP_PrintWarning(const E3DRSP_Warning* warning)
{
	PrintWarning(Warning(
		warning->Code,
		warning->Details,
		warning->Severity,
		warning->Extra
	));
}