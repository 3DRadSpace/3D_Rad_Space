#pragma once
#include "../Libs.hpp"

namespace Engine3DRadSpace::Internal
{
	enum class InitializationFlag : uint8_t
	{
		NoInitialization,
		InternalValidation,
		Initialize,
		Load,
		InitializeAndLoad
	};
}