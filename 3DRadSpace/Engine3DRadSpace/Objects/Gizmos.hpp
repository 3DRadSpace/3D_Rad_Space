#pragma once
#include "../Objects/Gizmos/Gizmo.hpp"
#include "../Reflection/UUID.hpp"

extern E3DRSP_OBJECTS_EXPORT std::vector<std::pair<Engine3DRadSpace::Reflection::UUID, std::unique_ptr<Engine3DRadSpace::Objects::Gizmos::IGizmo>>> e3drsp_gizmos;

namespace Engine3DRadSpace::Internal
{
	/// <summary>
	/// Returns the gizmo associated with the given UUID, or nullptr if no such gizmo exists.
	/// </summary>
	/// <param name="uuid">The UUID of the object whose gizmo is to be retrieved.</param>
	/// <returns>Pointer to the gizmo, or nullptr if no such gizmo exists.</returns>
	E3DRSP_OBJECTS_EXPORT Objects::Gizmos::IGizmo* GizmoOf(const Reflection::UUID& uuid);

	/// <summary>
	/// Returns the gizmo associated with the given reflectable object, or nullptr if no such gizmo exists. If no gizmo exists for the object, a new gizmo is created and associated with the object's UUID.
	/// </summary>
	/// <typeparam name="O">The type of the reflectable object.</typeparam>
	/// <param name="object">Pointer to the reflectable object.</param>
	/// <returns>Pointer to the gizmo, or nullptr if no such gizmo exists.</returns>
	template<Reflection::ReflectableObject O>
	Objects::Gizmos::IGizmo* GizmoOf(const O* object)
	{
		if(object == nullptr) return nullptr;

		auto possibleGizmo = GizmoOf(object->GetUUID());
		if(possibleGizmo != nullptr) return possibleGizmo;

		std::unique_ptr<Engine3DRadSpace::Objects::Gizmos::IGizmo> gizmo;
		gizmo.reset(new Objects::Gizmos::Gizmo<O>());
		auto result = gizmo.get();

		e3drsp_gizmos.emplace_back(
			object->GetUUID(),
			std::move(gizmo)
		);

		return result;
	}
	/// <summary>
	/// Frees all gizmos and clears the internal gizmo storage.
	/// </summary>
	E3DRSP_OBJECTS_EXPORT void UnloadGizmos();
}