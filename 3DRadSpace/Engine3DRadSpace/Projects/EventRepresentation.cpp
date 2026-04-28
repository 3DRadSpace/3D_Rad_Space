#include "EventRepresentation.hpp"
#include "../Objects/ObjectList.hpp"
#include "../Objects/Impl/Objects.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;
using namespace Engine3DRadSpace::Objects;

std::any EventInvocationRepresentation::Invoke(ObjectList* list)
{
	auto obj = list->operator[](OwnerObject);
	return Invoke(obj);
}

IReflectedFunction* EventInvocationRepresentation::FindFunction(IObject* object, size_t idxFn)
{
	auto reflObject = Internal::GetReflDataFromUUID(object->GetUUID());
	if (reflObject == nullptr) return nullptr;

	size_t id = 0;

	for (auto& f : *reflObject)
	{
		auto fn = dynamic_cast<IReflectedFunction*>(f);
		if (fn == nullptr) continue;

		if (id++ == idxFn)
		{
			return fn;
		}
	}

	return nullptr;
}

std::any EventInvocationRepresentation::Invoke(IObject* obj)
{
	auto fn = FindFunction(obj, FunctionID);
	if (fn != nullptr) return fn->Invoke(obj, Args);

	return std::any();
}

std::optional<Event> EventRepresentation::Reconstruct(ObjectList* list) const
{
	Event e;

	for (auto& fn : BoundFunctions)
	{
		auto fnRelPtr = fn.FindFunction(list->operator[](fn.OwnerObject), fn.FunctionID)->Clone().release();
		if(!fnRelPtr) continue;

		auto fnPtr = dynamic_cast<IReflectedFunction*>(fnRelPtr);
		if (!fnPtr)
		{
			delete fnRelPtr;
			continue;
		}

		std::unique_ptr<IReflectedFunction> boundFn;
		boundFn.reset(fnPtr);

		e.Bind(std::move(boundFn));
	}

	return std::nullopt;
}