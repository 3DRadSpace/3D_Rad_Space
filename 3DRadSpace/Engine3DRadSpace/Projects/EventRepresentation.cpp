#include "EventRepresentation.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;

std::optional<Event> EventRepresentation::Reconstruct(const Reflection::UUID& uuid) const
{
	Event e;

	if (BoundFunctions.empty()) return std::nullopt;

	for (auto& fn : BoundFunctions)
	{
		auto fnRelPtr = fn.FindFunction(uuid, fn.FunctionID);
		if (!fnRelPtr) continue;

		auto clonedFn = static_cast<IReflectedFunction*>(fnRelPtr->Clone().release());
		std::unique_ptr<IReflectedFunction> boundFn;
		boundFn.reset(clonedFn);
		
		e.Bind(std::move(boundFn));
	}

	return e;
}

EventRepresentation::EventRepresentation(const Reflection::Event& event, const Reflection::UUID& uuid)
{
	for (size_t i = 0; i < event.Count(); i++)
	{
		EventInvocationRepresentation fnRepr;
		fnRepr.FunctionID = i;
		//fnRepr.OwnerObject = event.At(i).Object;


	}
}