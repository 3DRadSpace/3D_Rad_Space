#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Box.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D box object in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Box : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Box> _box;
	public:
		/// <summary>
		///	Constructs a new Box object with the specified parameters.
		/// </summary>
		/// <param name="name">The name of the box.</param>
		/// <param name="visible">Whether the box is visible.</param>
		/// <param name="pos">The position of the box.</param>
		/// <param name="rotation">The rotation of the box.</param>
		/// <param name="scale">The scale of the box.</param>
		/// <param name="colour">The color of the box.</param>
		Box(
			const std::string& name = "Box",
			bool visible = true,
			const Math::Vector3& pos = Math::Vector3::Zero(),
			const Math::Quaternion& rotation = Math::Quaternion(),
			const Math::Vector3& scale = Math::Vector3::One(),
			const Math::Color& colour = Math::Color(1.0f, 1.0f, 1.0f, 1.0f)
		);
		/// <summary>
		/// Move constructor for the Box class. Transfers ownership of resources from another Box instance.
		/// </summary>
		/// <param name=""></param>
		Box(Box&&) noexcept = default;
		/// <summary>
		/// Move assignment operator for the Box class. Transfers ownership of resources from another Box instance.
		/// </summary>
		/// <param name="other">The other Box instance to move from.</param>
		/// <returns>A reference to this Box instance.</returns>
		Box& operator=(Box&&) noexcept = default;
		/// <summary>
		/// Color this box will be rendered with.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		/// Unused.
		/// </summary>
		void Initialize() override;
		/// <summary>
		///	(Re)creates the box primitive.
		/// </summary>
		void Load() override;
		/// <summary>
		///	Calls Load() without parameters.
		/// </summary>
		/// <param name="unused">unused</param>
		void Load(const std::filesystem::path& unused) override;
		/// <summary>
		/// Does nothing. Use ::Load() to recreate the box primitive.
		/// </summary>
		void Update() override;
		/// <summary>
		/// Draws the box in 3D space.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Checks if the given ray intersects with the box.
		/// </summary>
		/// <param name="r">The ray to test for intersection.</param>
		/// <returns>The distance to the intersection point, or NaN if there is no intersection.</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Returns an unique identifier for this object type.
		/// </summary>
		/// <returns>A unique identifier for the Box object type.</returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Returns a pointer to the gizmo associated with this box object.
		/// </summary>
		/// <returns>A pointer to the gizmo associated with this box object.</returns>
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		/// Gets the geometric primitive object for this class.
		/// </summary>
		/// <returns>Box primitive</returns>
		Graphics::Primitives::Box* GetPrimitive() const noexcept;

		~Box() override = default;
	};
}

REFL_FWD(Box)