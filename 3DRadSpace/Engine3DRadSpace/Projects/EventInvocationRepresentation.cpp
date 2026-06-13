#include "EventInvocationRepresentation.hpp"
#include "../Objects/Impl/Objects.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Projects;
using namespace Engine3DRadSpace::Reflection;

EventInvocationRepresentation::EventInvocationRepresentation() :
	OwnerObject(std::numeric_limits<size_t>::max()),
	FunctionID(std::numeric_limits<size_t>::max())
{
}

IReflectedFunction* EventInvocationRepresentation::FindFunction(const Reflection::UUID& uuid, size_t idxFn)
{
	auto reflObject = Internal::GetReflDataFromUUID(uuid);
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