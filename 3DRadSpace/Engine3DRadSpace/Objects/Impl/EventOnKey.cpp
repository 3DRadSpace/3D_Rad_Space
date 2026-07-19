#include "EventOnKey.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

EventOnKey::EventOnKey(
	const std::string& name,
	bool enabled,
	Input::Key key,
	const Reflection::Event& event
) : IObject(name, enabled, false),
	Key(key),
	Event(event)
{
}

void EventOnKey::Initialize()
{
}

void EventOnKey::Update()
{
	if (!Enabled) return;

	auto game = static_cast<Game*>(_game);
	
	if (game->Keyboard.IsKeyDown(Key))
		Event.InvokeAll();
}

void EventOnKey::Load()
{
}

void EventOnKey::Load(const std::filesystem::path& path)
{
}

Reflection::UUID EventOnKey::GetUUID() const noexcept
{
	// {F9DDFF6A-1D2C-4A0D-9175-E2459E4F75D2}
	return { 0xf9ddff6a, 0x1d2c, 0x4a0d, { 0x91, 0x75, 0xe2, 0x45, 0x9e, 0x4f, 0x75, 0xd2 } };
}

Gizmos::IGizmo* EventOnKey::GetGizmo() const noexcept
{
	return nullptr;
}

REFL_BEGIN(EventOnKey, "EventOnKey", "Events", "Invokes an event when a key is pressed.")
	REFL_FIELD(EventOnKey, std::string, Name, "Name", "EventOnKey", "Name of the object")
	REFL_FIELD(EventOnKey, bool, Enabled, "Enabled", true, "Whether the object is enabled or not.")
	REFL_FIELD(EventOnKey, Input::Key, Key, "Key", Input::Key::Space, "Key that triggers the event when pressed.")
	REFL_FIELD(EventOnKey, Reflection::Event, Event, "Event", {}, "Event to invoke when the key is pressed.")
REFL_END
