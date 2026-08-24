#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Sphere.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a procedurally generated 3D sphere primitive.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Sphere : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Sphere> _sphere;
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		Sphere();

		Sphere(Sphere&&) noexcept = default;
		Sphere& operator=(Sphere&&) noexcept = default;

		/// <summary>
		/// Colour of the sphere.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		/// Radius of the sphere.
		/// </summary>
		float Radius;
		/// <summary>
		/// Number of subdivisions used to generate the sphere's mesh.
		/// </summary>
		unsigned Resolution;

		/// <summary>
		/// Generates the sphere's mesh using the current Radius and Resolution.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="unused">Ignored.</param>
		void Load(const std::filesystem::path& unused) override;
		/// <summary>
		/// Does nothing.
		/// </summary>
		void Update() override;

		/// <summary>
		/// Draws the sphere.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Tests for intersections with the sphere.
		/// </summary>
		/// <param name="r">Ray to test against</param>
		/// <returns>Distance to the intersection point, or a negative value if there is no intersection</returns>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Gets the local transformation matrix of the sphere.
		/// </summary>
		/// <returns>Local matrix</returns>
		Math::Matrix4x4 GetLocalMatrix() const override;

		/// <summary>
		/// Gets the UUID of the Sphere type.
		/// </summary>
		/// <returns>{F7A76B8D-A2C4-47BE-8625-3B845507B979}</returns>
		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		/// Gets the underlying sphere primitive.
		/// </summary>
		/// <returns>Pointer to the underlying sphere primitive</returns>
		Graphics::Primitives::Sphere* GetPrimitive() const noexcept;

		~Sphere() override = default;
	};
}

REFL_FWD(Sphere)