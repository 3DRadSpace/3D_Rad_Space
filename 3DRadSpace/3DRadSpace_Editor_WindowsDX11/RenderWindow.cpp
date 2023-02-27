#include "RenderWindow.hpp"
#include <DirectXMath.h>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	simpleShader(std::make_unique<BlankShader>(Device.get())),
	editorWindow(parent)
{

}

void RenderWindow::Initialize()
{
	this->simpleShader = std::make_unique<BlankShader>(Device.get());

	std::vector<VertexPositionColor> dLines =
	{
		//+X
		VertexPositionColor{Vector3(0,0,0),Colors::Red},
		VertexPositionColor{Vector3(500,0,0),Colors::Red},
		//-X
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(-500,0,0),Colors::White},
		//+Y
		VertexPositionColor{Vector3(0,0,0),Colors::Green},
		VertexPositionColor{Vector3(0,500,0),Colors::Green},
		//-Y
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,-500,0),Colors::White},
		//+Z
		VertexPositionColor{Vector3(0,0,0),Colors::Blue},
		VertexPositionColor{Vector3(0,0,500),Colors::Blue},
		//-Z
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,0,-500),Colors::White},
	};

	for (int i = -10; i < 10; i++)
	{
		if (i == 0) continue;
		dLines.push_back(VertexPositionColor{ Vector3(i,0,10),Colors::Gray });
		dLines.push_back(VertexPositionColor{ Vector3(-i,0,-10),Colors::Gray });
	}

	this->lines = std::make_unique<VertexBuffer<VertexPositionColor>>(Device.get(), dLines, simpleShader->GetVertexShader());
	Camera.Position.Z = 1;

	lineRasterizer = std::make_unique<RasterizerState>(Device.get());
	lineRasterizer->CullMode = RasterizerCullMode::None;
}

void RenderWindow::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	zoom = mouse.ScrollWheel();

	if (mouse.RightButton() && IsFocused())
	{
		Point screenCenter = Window->Size() / 2;
		Point mousePos = mouse.Position();
		Window->SetMousePosition(screenCenter);

		Vector2 mouseDelta = (Vector2(screenCenter.X, screenCenter.Y) - Vector2(mousePos.X, mousePos.Y)) * dt;
		cameraPos -= mouseDelta * 0.1f;

		//cameraPos.Y = std::clamp<float>(cameraPos.Y, -std::numbers::pi / 2.f + 0.001f, std::numbers::pi / 2.f - 0.001f);
	}

	Quaternion q = Quaternion::FromYawPitchRoll(cameraPos.X, 0, 0) * Quaternion::FromYawPitchRoll(0, cameraPos.Y, 0);

	Camera.Position = Vector3::UnitZ().Transform(q) * (zoom + 5);
	timer += dt;
	Camera.SetLookAt(cursor3D);
}

void RenderWindow::Draw(Matrix &view, Matrix &projection, double dt)
{
	Camera.Draw(view, projection, dt);

	//auto XMlookAt = DirectX::XMMatrixLookAtRH({ Camera.Position.X, Camera.Position.Y, Camera.Position.Z }, { 0,0,0 }, { 0,1,0 });
	//auto XMproj = DirectX::XMMatrixPerspectiveFovRH(Math::ToRadians(65.0f), 4.f / 3.f, 0.01f, 500.f);

	//auto mvp = XMlookAt * XMproj;

	Matrix viewProj = view * projection;
	//memcpy(&viewProj, &mvp, sizeof(Matrix));

	simpleShader->SetBasic();
	Device->SetRasterizerState(lineRasterizer.get());
	simpleShader->SetTransformation(viewProj);
	Device->SetTopology(VertexTopology::LineList);
	lines->SetAndDraw(0);
}

bool RenderWindow::IsFocused()
{
	return editorWindow == GetForegroundWindow();
}

void RenderWindow::Reset3DCursor()
{
	cursor3D = Vector3::Zero();
}
