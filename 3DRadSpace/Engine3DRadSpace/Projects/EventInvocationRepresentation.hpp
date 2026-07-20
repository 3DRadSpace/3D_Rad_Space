#pragma once
#include "../Reflection/Event.hpp"

namespace Engine3DRadSpace::Objects
{
	class ObjectList;
}

namespace Engine3DRadSpace::Projects
{
	/// <summary>
	/// Serializable representation of a member function call.
	/// </summary>
	struct E3DRSP_PROJECTS_EXPORT EventInvocationRepresentation
	{
		/// <summary>
		/// ID of the object in the ObjectList.
		/// </summary>
		size_t OwnerObject;
		/// <summary>
		/// ID of the function, per reflection metadata.
		/// </summary>
		size_t FunctionID;
		/// <summary>
		/// Arguments pack.
		/// </summary>
		std::vector<std::any> Args;

		EventInvocationRepresentation();

		static Reflection::IReflectedFunction* FindFunction(Reflection::ReflectedObject* reflObject, size_t idxFn);
	};
}