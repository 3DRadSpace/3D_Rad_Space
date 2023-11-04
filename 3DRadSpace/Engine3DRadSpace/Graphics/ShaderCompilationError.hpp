#pragma once
#include "../Logging/Exception.hpp"

namespace Engine3DRadSpace::Graphics
{
	class DLLEXPORT ShaderCompilationError : public Logging::Exception
	{
	public:
		ShaderCompilationError(const std::string &err) :
			Exception(err)
		{
		}
	};
}

