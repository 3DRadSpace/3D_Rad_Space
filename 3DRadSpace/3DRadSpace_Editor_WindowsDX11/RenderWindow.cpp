#include "RenderWindow.hpp"
#include <cassert>

RenderWindow::RenderWindow(HWND parent, HINSTANCE hInstance) : 
	Game(Engine3DRadSpace::Window(hInstance,parent)),
	_triangleShader(Device.get())
{

}

void RenderWindow::Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt)
{

}

void RenderWindow::Draw(double dt)
{

}
