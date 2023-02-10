#include "RenderWindow.hpp"
#include <cassert>

RenderWindow::RenderWindow(Engine3DRadSpace::Window* w) : Game(w), _triangleShader(Device.get())
{
	assert(_CrtCheckMemory());
}

void RenderWindow::Update(Engine3DRadSpace::Input::Keyboard& keyboard, Engine3DRadSpace::Input::Mouse& mouse, double dt)
{

}

void RenderWindow::Draw(double dt)
{

}
