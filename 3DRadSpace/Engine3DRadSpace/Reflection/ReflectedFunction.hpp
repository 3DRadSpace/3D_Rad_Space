#pragma once
#include "FieldRepresentation.hpp"

namespace Engine3DRadSpace::Reflection
{
	class DLLEXPORT IReflectedFunction
	{
	public:
		virtual unsigned int NumParameters() = 0;
		virtual std::vector<FieldRepresentation> ParametersInfo() = 0;
		virtual FieldRepresentation ReturnedTypeInfo() = 0;
		virtual const char *Name() = 0;

		virtual ~IReflectedFunction() = default;
	};

	/*
	template<typename Obj, typename Fn>
	class ReflectedFunction {};

	template<typename Obj, typename R, ReflectableType... Args>
	class ReflectedFunction<Obj, R(Args...)>
	{
		unsigned _numParams = sizeof...(Args);
		std::vector<FieldRepresentation> _parametersInfo;
		FieldRepresentation _retType;
		
		template<ReflectableType A>
		void _initializeParams(A a)
		{
			_parametersInfo.push_back(GetFieldRepresentation<A>());
		}

		template<ReflectableType A, ReflectableType ...Args>
		void _initializeParams(A a, Args... args)
		{
			_initializeParams<A>(a);
			_initializeParams<Args>(args);
		}
	};
	*/

}