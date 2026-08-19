#pragma once
#include "Gizmo.hpp"
#include "../Impl/SoundSource.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ITexture2D;

	namespace Primitives
	{
		class SphericalBillboard;
	}
}

namespace Engine3DRadSpace::Objects::Gizmos
{
	template<>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT Gizmo<SoundSource> final : public IGizmo
	{
		std::unique_ptr<Graphics::Primitives::SphericalBillboard> _billboard;
		std::unique_ptr<Graphics::ITexture2D> _soundImage;
	public:
		Gizmo();

		void Draw3D() override;
		void Draw2D() override;
		void Load() override;
		void Load(const std::filesystem::path& path) override;
		void Update() override;

		~Gizmo();
	};
}