#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Cone.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT Cone : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Cone> _cone;
	public:
		Cone();

		Math::Color Colour;
		float Radius;
		float Height;
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
		Graphics::Primitives::Cone* GetPrimitive() const noexcept;
	
		~Cone() override = default;
	};
}

REFL_FWD(Cone)