#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Cone.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents an cone object in 3D space.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Cone : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Cone> _cone;
	public:
		/// <summary>
		/// Initializes a new instance of the Cone class.
		/// </summary>
		Cone();

		Cone(Cone&&) noexcept = default;
		Cone& operator=(Cone&&) noexcept = default;
		/// <summary>
		///	Color of the cone. This is used when generating the cone primitive.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		/// Radius of the cone.
		/// </summary>
		float Radius;
		/// <summary>
		/// Height of the cone.
		/// </summary>
		float Height;
		/// <summary>
		///	Tesellation resolution of the cone. Higher values will result in a smoother surface, but will consume memory.
		/// </summary>
		unsigned Resolution;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		///	(Re)creates the cone primitive shape.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Same as Load() without arguments.
		/// </summary>
		/// <param name="unused">unused</param>
		void Load(const std::filesystem::path& unused) override;
		/// <summary>
		/// Does nothing.
		void Update() override;
		/// <summary>
		///	Draws the cone.
		/// </summary>
		void Draw3D() override;
		/// <summary>
		/// Returns the distance from the ray origin to the intersection point, or NaN if there is no intersection.
		/// </summary>
		float Intersects(const Math::Ray& r) const override;
		/// <summary>
		/// Returns the local transform matrix of this object.
		/// </summary>
		/// <returns>Scale(R,H,R)*Rotation*Translation matrix</returns>
		Math::Matrix4x4 GetLocalMatrix() const override;
		/// <summary>
		///	Gets the type identifier of this object.
		/// </summary>
		/// <returns></returns>
		Reflection::UUID GetUUID() const noexcept override;
		/// <summary>
		/// Gets the gizmo associated with this object. Returns nullptr if no gizmo is associated.
		/// </summary>
		/// <returns></returns>
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		/// <summary>
		/// Gets the primitive shape of this object. Returns nullptr if no primitive is associated.
		/// </summary>
		/// <returns>The primitive shape of this object.</returns>
		Graphics::Primitives::Cone* GetPrimitive() const noexcept;
	
		~Cone() override = default;
	};
}

REFL_FWD(Cone)