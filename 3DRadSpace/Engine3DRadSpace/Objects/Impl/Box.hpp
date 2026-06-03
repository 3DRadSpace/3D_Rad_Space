#pragma once
#include "../IObject3D.hpp"
#include "../../Graphics/Primitives/Box.hpp"
#include "../../Reflection/Reflection.hpp"

namespace Engine3DRadSpace::Objects
{
	class E3DRSP_OBJECTS_IMPL_EXPORT Box : public IObject3D
	{
		std::unique_ptr<Graphics::Primitives::Box> _box;
	public:
		Box();

		Math::Color Colour;

		void Initialize() override;
		void Load() override;
		void Load(const std::filesystem::path& unused) override;
		void Update() override;

		void Draw3D() override;
		float Intersects(const Math::Ray& r);

		Reflection::UUID GetUUID() const noexcept override;
		Objects::Gizmos::IGizmo* GetGizmo() const noexcept override;
	
		Graphics::Primitives::Box* GetPrimitive() const noexcept;

		~Box() override = default;
	};
}

REFL_FWD(Box)