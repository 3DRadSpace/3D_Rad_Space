#pragma once
#include "Gizmo.hpp"
#include "../Impl/TextPrint.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<TextPrint> : public IGizmo
	{
	public:
		Gizmo();

		void Load() override;
		void Load(const std::filesystem::path& path) override;

		void Draw3D() override;
		void Draw2D() override;

		void Update() override;

		~Gizmo() = default;
	};
}