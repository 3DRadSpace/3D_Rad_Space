#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Sphere.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT Sphere : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Sphere> _sphere;
	public:
		Sphere();

		Math::Color Colour;
		float Radius;
		unsigned Resolution;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& unused) override;
		void Update() override;

		void Draw3D() override;
		float Intersects(const Math::Ray& r) override;
		Math::Matrix4x4 GetLocalMatrix() override;

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
		Graphics::Primitives::Sphere* GetPrimitive() const noexcept;
	
		~Sphere() override = default;
	};
}

REFL_FWD(Sphere)