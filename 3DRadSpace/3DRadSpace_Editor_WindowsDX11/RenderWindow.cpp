#include "RenderWindow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Math;

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	_triangleShader(Device.get())
{

}

void RenderWindow::Initialize()
{
	std::array<VertexPositionColor,3> triangle =
	{
		VertexPositionColor{Vector3(0.0,0.5,0.0), Colors::Red},
		VertexPositionColor{Vector3(0.5,-0.5,0.0), Colors::Green},
		VertexPositionColor{Vector3(-0.5,-0.5,0.0), Colors::Blue}
	};

	_triangleBuffer = std::make_unique<VertexBuffer<VertexPositionColor>>(Device.get(), triangle, _triangleShader.GetVertexShaderRef());
}

void RenderWindow::Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt)
{

}

void RenderWindow::Draw(double dt)
{
	_triangleShader.SetBasic();
	Device->SetTopology(VertexTopology::TriangleList);
	_triangleBuffer->SetAndDraw();
}
