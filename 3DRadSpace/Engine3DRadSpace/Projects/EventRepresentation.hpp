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
	struct EventInvocationRepresentation
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

		std::any Invoke(Objects::ObjectList* list);
		std::any Invoke(Objects::IObject* obj);

		static Reflection::IReflectedFunction* FindFunction(Objects::IObject* obj, size_t idxFn);
	};

	/// <summary>
	/// Serializable representation of an <see cref="Event"/>.
	/// </summary>
	struct EventRepresentation
	{
		std::vector<EventInvocationRepresentation> BoundFunctions;

		std::optional<Reflection::Event> Reconstruct(Objects::ObjectList* list) const;
	};
}