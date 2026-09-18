#include "ScannerGizmo.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Primitives;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Scanner>::Gizmo()
{
	Allow2DRendering = false;
	AllowRotating = true;
	AllowScaling = false;
}

void Gizmo<Scanner>::Load()
{
	if (!_arrow)
	{
		_arrow = std::make_unique<Arrow>(
			Object->GetGraphicsDeviceHandle(),
			Vector2(0.0625f, 1.0f),
			Colors::LightOrange
		);
	}
}

void Gizmo<Scanner>::Load(const std::filesystem::path& path)
{
	Load();
}

void Gizmo<Scanner>::Draw3D()
{
	if (!Object) return;
	if (!Object->Visible) return;

	auto scanner = dynamic_cast<Scanner*>(Object);
	if (scanner == nullptr) return;

	_arrow->Transform = Matrix4x4::CreateScale(Vector3(1.0f, scanner->MaxDistance, scanner->MaxDistance)) * scanner->GetModelMatrix();

	auto g = static_cast<Game*>(Object->GetGame());
	_arrow->View = g->Cameras->GetActiveCamera()->GetViewMatrix();
	_arrow->Projection = g->Cameras->GetActiveCamera()->GetProjectionMatrix();

	_arrow->Draw3D();
}

void Gizmo<Scanner>::Draw2D()
{
}

void Gizmo<Scanner>::Update()
{
}