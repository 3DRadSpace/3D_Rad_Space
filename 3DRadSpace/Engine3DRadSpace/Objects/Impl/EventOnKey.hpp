#pragma once
#include "../IObject.hpp"
#include "../../Reflection/Event.hpp"
#include "../../input/Key.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT EventOnKey : public IObject
	{
	public:
		EventOnKey(
			const std::string& name = "EventOnKey",
			bool enabled = true,
			Input::Key key = Input::Key::Space,
			const Reflection::Event& event = {}
		);

		EventOnKey(EventOnKey&&) noexcept = default;
		EventOnKey& operator=(EventOnKey&&) noexcept = default;

		Input::Key Key;
		Reflection::Event Event;

		void Initialize() override;
		void Update() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;

		Reflection::UUID GetUUID() const noexcept override;
		Gizmos::IGizmo* GetGizmo() const noexcept override;
	};
}