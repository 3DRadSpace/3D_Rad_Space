#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Cylinder.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	/// Represents a 3D cylinder object in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_IMPL_EXPORT Cylinder : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Cylinder> _cylinder;
	public:
		///<summary>
		/// Constructs a Cylinder object with the specified parameters.
		/// </summary>
		Cylinder();
		/// <summary>
		///	Color of this cylinder.
		/// </summary>
		Math::Color Colour;
		/// <summary>
		///	Radius of this cylinder.
		/// </summary>
		float Radius;
		/// <summary>
		/// Height of this cylinder.
		/// </summary>
		float Height;
		/// <summary>
		/// Tesellation of this cylinder.
		/// </summary>
		unsigned Resolution;
		/// <summary>
		///	Does nothing.
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// (Re)creates the cylinder primitive with the current parameters.
		/// </summary>
		void Load() override;
		/// <summary>
		/// Calls Load() without arguments.
		/// </summary>
		/// <param name="unused">unused</param>
		void Load(const std::filesystem::path& unused) override;
		void Update() override;

		void Draw3D() override;
		float Intersects(const Math::Ray& r) const override;
		Math::Matrix4x4 GetLocalMatrix() const override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		Graphics::Primitives::Cylinder* GetPrimitive() const noexcept;

		~Cylinder() override = default;
	};
}

REFL_FWD(Cylinder)