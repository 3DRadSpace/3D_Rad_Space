#include "ErrorCallback.hpp"
#include "../../Logging/Message.hpp"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace::Physics::NVPhysX;
using namespace Engine3DRadSpace::Logging;

void ErrorCallback::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
{
	Logging::PrintWarning(std::format("PhysX {} in file: {} at line: {}", message, file, line));
}