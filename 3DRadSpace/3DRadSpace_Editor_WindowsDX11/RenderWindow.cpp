#include "RenderWindow.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::Shaders;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Input;

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) :
	Game(Engine3DRadSpace::Window(hInstance, parent)),
	simpleShader(std::make_unique<BlankShader>(Device.get()))
{

}

void RenderWindow::Initialize()
{
	std::array<VertexPositionColor,12> dLines =
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
		VertexPositionColor{Vector3(0,0,0),Colors::Green},
		VertexPositionColor{Vector3(0,0,500),Colors::Green},
		//-Z
		VertexPositionColor{Vector3(0,0,0),Colors::White},
		VertexPositionColor{Vector3(0,0,-500),Colors::White},
	};

	this->lines = std::make_unique<VertexBuffer<VertexPositionColor>>(Device.get(), lines, simpleShader->GetVertexShader());
}

void RenderWindow::Update(Keyboard& keyboard, Mouse& mouse, double dt)
{
	if (mouse.RightButton())
	{
		mouse.SetPosition(this->Device->Resolution() / 2.0f);
	}
}

void RenderWindow::Draw(Matrix &view, Matrix &projection, double dt)
{

}
