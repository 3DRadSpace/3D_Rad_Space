#pragma once
#include "../Core/Libs.hpp"

namespace Engine3DRadSpace::Native
{
	/// <summary>
	/// Utility function. Sets the working directory of the current process to the directory where the executable is located on the filedisk.
	/// </summary>
	E3DRSP_NATIVE_EXPORT void SetDefaultWorkingDirectory();
}