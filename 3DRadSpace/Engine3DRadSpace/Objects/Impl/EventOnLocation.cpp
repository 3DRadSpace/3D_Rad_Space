#include "EventOnLocation.hpp"
#include "../ObjectList.hpp"
#include "../Gizmos.hpp"
#include "../Gizmos/EOLGizmo.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;

EventOnLocation::EventOnLocation(
	const std::string& name,
	bool enabled,
	bool visible,
	const Math::Vector3& pos,
	const Math::Vector3& scale,
	const Reflection::Event& event,
	const ObjectID trackedObject,
	float tolerance
) : IObject3D(name, enabled, visible, pos, Vector3::Zero(), Math::Quaternion(), scale),
	Event(event),
	TrackedObject(trackedObject),
	Tolerance(tolerance)
{
}

void EventOnLocation::Initialize()
{
}

void EventOnLocation::Load()
{
}

void EventOnLocation::Load(const std::filesystem::path& unused)
{
	(void)unused;
}

void EventOnLocation::Update()
{
	if (!Enabled) return;

	auto trackedObj = TrackedObject.Get(GetGame()->RequireService<ObjectList>({}));
	if (trackedObj == nullptr) return;

	auto trackedObj3D = dynamic_cast<IObject3D*>(trackedObj);
	if (trackedObj3D == nullptr) return;

	BoundingBox box(Position, Scale);
	BoundingSphere sphere(Position, Scale.X);

	BoundingSphere objSph(trackedObj3D->Position, Tolerance);

	bool intersects = IsSphere ? sphere.Intersects(objSph) : box.Intersects(objSph);
	if (intersects)
	{
		Event.InvokeAll();
	}
}

void EventOnLocation::Draw3D()
{
	auto gizmo = Internal::GizmoOf<EventOnLocation>(this);
	if (gizmo != nullptr && Visible)
	{
		gizmo->Draw3D();
	}
}

float EventOnLocation::Intersects(const Math::Ray& r)
{
	BoundingBox box(Position, Scale);
	BoundingSphere sphere(Position, Scale.X);

	if (IsSphere)
	{
		return r.Intersects(sphere);
	}
	else return r.Intersects(box);
}

Gizmos::IGizmo* EventOnLocation::GetGizmo() const noexcept
{
	return Internal::GizmoOf<EventOnLocation>(this);
}

Reflection::UUID EventOnLocation::GetUUID() const noexcept
{
	// {043F89A6-D54B-497D-AF5D-7C1C6158515A}
	return { 0x43f89a6, 0xd54b, 0x497d, { 0xaf, 0x5d, 0x7c, 0x1c, 0x61, 0x58, 0x51, 0x5a } };
}

REFL_BEGIN(EventOnLocation, "EventOnLocation", "Events", "An object that triggers an event when a tracked object enters a specified area.")
	REFL_FIELD(EventOnLocation, std::string, Name, "Name", "EventOnLocation", "Object's name.")
	REFL_FIELD(EventOnLocation, bool, Enabled, "Enabled", true, "Whether the event is active or not.")
	REFL_FIELD(EventOnLocation, bool, Visible, "Visible", false, "Whether the bounding shape is visible in the scene or not.")
	REFL_FIELD(EventOnLocation, Math::Vector3, Position, "Position", Vector3::Zero(), "EventOnLocation's position in world space.")
	REFL_FIELD(EventOnLocation, Math::Vector3, Scale, "Scale", Vector3::One(), "EventOnLocation's scale. If IsSphere is true, only the X component is used as the radius of the sphere.")
	REFL_FIELD(EventOnLocation, float, Tolerance, "Tolerance", 0.1f, "The event will be triggered if the tracked object is within this distance from the bounding shape.")
	REFL_FIELD(EventOnLocation, bool, IsSphere, "Is sphere", false, "Determines if the area is either an sphere(true) or AABB(false).")
	REFL_FIELD(EventOnLocation, ObjectID, TrackedObject, "Tracked object", 0, "The tracked object. If the selected specific object is inside the bounding shape, then the event is triggered.")
	REFL_FIELD(EventOnLocation, Reflection::Event, Event, "Event", {}, "Executes each time the tracked object enters the area. Return value is ignored.")
	REFL_METHOD(EventOnLocation, void, &EventOnLocation::Enable, "Enable")
	REFL_METHOD(EventOnLocation, void, &EventOnLocation::Disable, "Disable")
REFL_END