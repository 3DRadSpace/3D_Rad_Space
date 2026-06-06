#pragma once
#include "Gizmo.hpp"
#include "../Impl/EventOnLocation.hpp"
#include "../../Graphics/Primitives/LineList.hpp"
#include "../../Graphics/Primitives/Sphere.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<EventOnLocation> final : public IGizmo
	{
		std::unique_ptr<Graphics::Primitives::LineList> _wireframeCube;
		std::unique_ptr<Graphics::Primitives::Sphere> _sphere;
		std::unique_ptr<Graphics::IRasterizerState> _wireframe_RasterizerState;
		std::unique_ptr<Graphics::IDepthStencilState> _depthStencilState;
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