#pragma once
#include "Gizmo.hpp"
#include "../Impl/Scanner.hpp"
#include "../../Graphics/Primitives/Arrow.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<Scanner> final : public IGizmo
	{
		std::unique_ptr<Graphics::Primitives::Arrow> _arrow;
	public:
		Gizmo();

		void Draw3D() override;
		void Draw2D() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		~Gizmo() = default;
	};
}