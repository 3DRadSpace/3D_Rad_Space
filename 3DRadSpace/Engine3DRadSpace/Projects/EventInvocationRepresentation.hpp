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
		/// <summary>
		/// Default constructor.
		/// </summary>
		EventInvocationRepresentation();
		/// <summary>
		///	Finds an reflected function from the given object and function index.
		/// </summary>
		/// <param name="reflObject">The reflected object to search for the function.</param>
		/// <param name="idxFn">The index of the function within the reflected object's function list.</param>
		/// <returns>The reflected function if found; otherwise, nullptr.</returns>
		static Reflection::IReflectedFunction* FindFunction(Reflection::ReflectedObject* reflObject, size_t idxFn);
	};
}