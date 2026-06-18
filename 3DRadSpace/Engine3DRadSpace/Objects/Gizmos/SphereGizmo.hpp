#pragma once
#include "Gizmo.hpp"
#include "../Impl/Sphere.hpp"
#include "../../Graphics/IRasterizerState.hpp"
#include "../../Graphics/IDepthStencilBuffer.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<Sphere> final : public IGizmo
	{
		bool _wasLoaded = false;
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
