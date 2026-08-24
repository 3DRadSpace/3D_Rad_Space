#pragma once
#include "../IObject.hpp"
#include "../../Reflection/Event.hpp"
#include "../../input/Key.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents an event that is triggered when a specific key is pressed.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT EventOnKey : public IObject
	{
	public:
		/// <summary>
		/// Complete EoK constructor. Initializes the object with a name, enabled state, key to listen for, and the event to trigger.
		/// </summary>
		/// <param name="name">Name of the object</param>
		/// <param name="enabled">Is the object enabled</param>
		/// <param name="key">Key to listen for</param>
		/// <param name="event">Event to trigger</param>
		explicit EventOnKey(
			const std::string& name = "EventOnKey",
			bool enabled = true,
			Input::Key key = Input::Key::Space,
			const Reflection::Event& event = {}
		);

		EventOnKey(EventOnKey&&) noexcept = default;
		EventOnKey& operator=(EventOnKey&&) noexcept = default;
		/// <summary>
		/// The key that will trigger the event when pressed.
		/// </summary>
		Input::Key Key;
		/// <summary>
		/// The event that will be triggered when the specified key is pressed.
		/// </summary>
		Reflection::Event Event;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Checks if the specified key is pressed and triggers the event if it is.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		///	Does nothing.
		/// </summary>
		/// <param name="path">unused</param>
		void Load(const std::filesystem::path& path) override;
		/// <summary>
		/// Gets the UUID of the EoK object type.
		/// </summary>
		/// <returns>{F9DDFF6A-1D2C-4A0D-9175-E2459E4F75D2}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		///	Returns null.
		/// </summary>
		/// <returns>Inexistent gizmo.</returns>
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}

REFL_FWD(EventOnKey)