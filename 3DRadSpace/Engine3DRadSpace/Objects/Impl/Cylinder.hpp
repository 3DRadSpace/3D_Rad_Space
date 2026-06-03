#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Cylinder.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT Cylinder : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Cylinder> _cylinder;
	public:
		Cylinder();

		Math::Color Colour;
		float Radius;
		float Height;
		unsigned Resolution;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& unused) override;
		void Update() override;

		void Draw3D() override;
		float Intersects(const Math::Ray& r);
		Math::Matrix4x4 GetLocalMatrix() override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;

		Graphics::Primitives::Cylinder* GetPrimitive() const noexcept;

		~Cylinder() override = default;
	};
}

REFL_FWD(Cylinder)