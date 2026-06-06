#pragma once
#include "../IObject3D.hpp"
#include "../../Reflection/Event.hpp"
#include "../ObjectID.hpp"
#include "../../Reflection/reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents an event object that executes an event when the player enters a specified area.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT EventOnLocation : public IObject3D
	{
	public:
		/// <summary>
		/// Constructs an event on location object.
		/// </summary>
		/// <param name="name">Object name</param>
		/// <param name="enabled">Is the event on location active?</param>
		/// <param name="event">Event to execute when the player enters the area</param>
		EventOnLocation(
			const std::string& name = "EventOnLocation",
			bool enabled = true,
			bool visible = false,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Vector3& scale = Math::Vector3::One(),
			const Reflection::Event& event = {},
			const ObjectID trackedObject = 0,
			float tolerance = 0.1f
		);

		EventOnLocation(EventOnLocation&&) noexcept = default;
		EventOnLocation& operator=(EventOnLocation&&) noexcept = default;

		/// <summary>
		/// Determines if the area is either an sphere(true) or AABB(false).
		/// </summary>
		bool IsSphere;

		/// <summary>
		/// The event will be triggered if the tracked object is within this distance from the bounding shape.
		/// </summary>
		float Tolerance = 0.1f;

		/// <summary>
		/// The tracked object. If the selected specific object is inside the bounding shape, then the event is triggered.
		/// </summary>
		ObjectID TrackedObject;
		/// <summary>
		/// Executes each time the tracked object enters the area. Return value is ignored.
		/// </summary>
		Reflection::Event Event;

		/// <summary>
		/// Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="unused">unused</param>
		void Load(const std::filesystem::path& unused) override;
		/// <summary>
		/// Checks if the tracked object is inside the bounding shape.
		/// </summary>
		void Update() override;
		
		/// <summary>
		/// Draws the bounding shape.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns the distance from the ray origin to the intersection point, or NaN if there is no intersection.
		/// </summary>
		/// <param name="r">Ray</param>
		/// <returns>Distance or NaN</returns>
		float Intersects(const Math::Ray& r) override;
		
		Gizmos::IGizmo* GetGizmo() const noexcept override;
		Reflection::UUID GetUUID() const noexcept override;

		~EventOnLocation() override = default;
	};
}

REFL_FWD(EventOnLocation)