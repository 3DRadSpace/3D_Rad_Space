#include "SoundSourceGizmo.hpp"
#include "../../Games/Game.hpp"
#include "../../Graphics/IRasterizerState.hpp"
#include "../../Graphics/ITexture2D.hpp"
#include "../../Graphics/Primitives/SphericalBillboard.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<SoundSource>::Gizmo()
{
	Allow2DRendering = false;
	AllowRotating = false;
	AllowScaling = false;
}

void Gizmo<SoundSource>::Load()
{
	if(Object == nullptr) return;
}

void Gizmo<SoundSource>::Load(const std::filesystem::path& path)
{
}

void Gizmo<SoundSource>::Draw3D()
{

}

void Gizmo<SoundSource>::Draw2D()
{

}

void Gizmo<SoundSource>::Update()
{

}

Gizmo<SoundSource>::~Gizmo()
{
}