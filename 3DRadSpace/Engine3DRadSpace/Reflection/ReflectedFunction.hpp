#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	class IReflectedFunctoin
	{
	public:
		virtual unsigned int NumParameters() = 0;
		virtual std::vector<FieldRepresentation> ParametersInfo() = 0;
		virtual FieldRepresentation ReturnedTypeInfo() = 0;
		virtual const char *Name() = 0;
		virtual void *FunctionAddress() = 0;

		virtual ~IReflectedFunctoin() = default;
	};

	int callFunction(void *fn)
	{
		__asm
		{
			xor rax,rax
			ret
		}
	}
}