#include "EOLGizmo.hpp"
#include "../../Games/Game.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<EventOnLocation>::Gizmo()
{
	Allow2DRendering = false;
	AllowRotating = false;
	AllowScaling = false;
}

void Gizmo<EventOnLocation>::Load()
{
	if (Object == nullptr) return;
	auto eol = static_cast<EventOnLocation*>(Object);

	auto device = eol->GetGraphicsDeviceHandle();
	if (_wireframeCube == nullptr)
	{
		std::vector<VertexPositionColor> boxWireframe = {
			// Bottom face (z=0)
			VertexPositionColor(Vector3(0.0f, 0.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 0.0f, 0.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 0.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 1.0f, 0.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 1.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 1.0f, 0.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(0.0f, 1.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 0.0f, 0.0f), Colors::LightGreen),

			// Top face (z=1)
			VertexPositionColor(Vector3(0.0f, 0.0f, 1.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 0.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 0.0f, 1.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 1.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 1.0f, 1.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 1.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(0.0f, 1.0f, 1.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 0.0f, 1.0f), Colors::LightGreen),

			// Vertical edges
			VertexPositionColor(Vector3(0.0f, 0.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 0.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 0.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 0.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(1.0f, 1.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(1.0f, 1.0f, 1.0f), Colors::LightGreen),

			VertexPositionColor(Vector3(0.0f, 1.0f, 0.0f), Colors::LightGreen),
			VertexPositionColor(Vector3(0.0f, 1.0f, 1.0f), Colors::LightGreen),
		};

		_wireframeCube = std::make_unique<Graphics::Primitives::LineList>(device, boxWireframe);
	}
	if (_sphere == nullptr)
	{
		_sphere = std::make_unique<Graphics::Primitives::Sphere>(device, 1.0f, Color(0.5f, 1.0f, 0.5f, 0.25f), 32);
	}
	if (_wireframe_RasterizerState == nullptr)
	{
		_wireframe_RasterizerState = device->CreateRasterizerState_Wireframe();
	}
	if (_depthStencilState == nullptr)
	{
		_depthStencilState = device->CreateDepthStencilState_DepthNone();
	}
}

void Gizmo<EventOnLocation>::Load(const std::filesystem::path& path)
{
	Load();
}

void Gizmo<EventOnLocation>::Draw3D()
{
	if (Object == nullptr) return;
	auto eol = static_cast<EventOnLocation*>(Object);
	auto transform = eol->GetModelMatrix();

	auto game = static_cast<Game*>(eol->GetGame());
	auto view = game->View;
	auto projection = game->Projection;

	if (!eol->IsSphere)
	{
		auto context = _wireframe_RasterizerState->GetGraphicsDevice()->ImmediateContext();
		auto oldRasterizerState = context->GetGraphicsDevice()->GetRasterizerState();

		context->SetRasterizerState(_wireframe_RasterizerState.get());

		_wireframeCube->Transform = transform;
		_wireframeCube->View = view;
		_wireframeCube->Projection = projection;
		_wireframeCube->Draw3D();

		context->SetRasterizerState(oldRasterizerState.get());
	}
	else
	{
		_sphere->Transform = transform;
		_sphere->View = view;
		_sphere->Projection = projection;
		_sphere->Draw3D();
	}
}

void Gizmo<EventOnLocation>::Draw2D()
{
}

void Gizmo<EventOnLocation>::Update()
{
}