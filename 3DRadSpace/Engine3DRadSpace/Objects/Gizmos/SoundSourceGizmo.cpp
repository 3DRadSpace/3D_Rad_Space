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
	auto device = Object->GetGraphicsDeviceHandle();

	if (_soundImage == nullptr)
	{
		_soundImage = device->CreateTexture2D("Data\\Sprites\\Sound.png");
	}

	if (_billboard == nullptr)
	{
		_billboard = std::make_unique<Primitives::CylindricalBillboard>(device);
		_billboard->Texture = _soundImage.get();
		_billboard->Axis = Math::Vector3::UnitY();
	}
	_cameras = Object->GetGame()->GetService<CameraProvider>({});
}

void Gizmo<SoundSource>::Load(const std::filesystem::path& path)
{
	Load();
}

void Gizmo<SoundSource>::Draw3D()
{
	auto camera = _cameras->GetActiveCamera();
	_billboard->Transform = dynamic_cast<IObject3D*>(Object)->GetModelMatrix();
	_billboard->View = camera->GetViewMatrix();
	_billboard->Projection = camera->GetProjectionMatrix();
	_billboard->Draw3D();
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