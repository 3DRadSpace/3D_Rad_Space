#pragma once
#include "EventInvocationRepresentation.hpp"

namespace Engine3DRadSpace::Projects
{
	/// <summary>
	/// Serializable representation of an <see cref="Event"/>.
	/// </summary>
	struct E3DRSP_PROJECTS_EXPORT EventRepresentation
	{
		std::vector<EventInvocationRepresentation> BoundFunctions;

		EventRepresentation() = default;
		EventRepresentation(const Reflection::Event& event, const Reflection::UUID& uuid);

		std::optional<Reflection::Event> Reconstruct(const Reflection::UUID &uuid) const;
	};
}