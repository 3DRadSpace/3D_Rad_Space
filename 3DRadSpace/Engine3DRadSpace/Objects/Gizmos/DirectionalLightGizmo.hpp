#pragma once
#include "Gizmo.hpp"
#include "../Impl/DirectionalLight.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<DirectionalLight> : public IGizmo
	{
		Math::Quaternion rotation;
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