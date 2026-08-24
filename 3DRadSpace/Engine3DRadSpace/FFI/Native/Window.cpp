#include "Window.h"
#include "../../Native/Window.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Native;

E3DRSP_Window E3DRSP_Window_Create(const char* title, size_t width, size_t height)
{
	return new Window(title, width, height);
}

void* E3DRSP_Window_NativeHandle(E3DRSP_Window window)
{
	return static_cast<Window*>(window)->NativeHandle();
}

void E3DRSP_Window_ProcessMessages(E3DRSP_Window window)
{
	static_cast<Window*>(window)->ProcessMessages();
}

E3DRSP_Mouse E3DRSP_Window_GetMouseState(E3DRSP_Window window)
{
	E3DRSP_Mouse r;

	auto mouse = static_cast<Window*>(window)->GetMouseState();

	r.LeftButton = static_cast<E3DRSP_ButtonState>(mouse.LeftButton());
	r.MiddleButton = static_cast<E3DRSP_ButtonState>(mouse.MiddleButton());

	auto p = mouse.Position();
	r.Position = {p.X, p.Y};

	r.RightButton = static_cast<E3DRSP_ButtonState>(mouse.LeftButton());
	r.ScrollWheel = mouse.ScrollWheel();

	return r;
}

E3DRSP_Keyboard E3DRSP_Window_GetKeyboardState(E3DRSP_Window window)
{
	E3DRSP_Keyboard kb;

	static_assert(sizeof(E3DRSP_Keyboard) == sizeof(Keyboard));

	auto keyboard = static_cast<Window*>(window)->GetKeyboardState();
	memcpy_s(&kb, sizeof(E3DRSP_Keyboard), &keyboard, sizeof(Keyboard)); // eeeh, would you prefer public_cast?

	return kb;
}

E3DRSP_Point E3DRSP_Window_Size(E3DRSP_Window window)
{
	auto s = static_cast<Window*>(window)->Size();
	E3DRSP_Point size = {s.X, s.Y};
	return size;
}

E3DRSP_RectangleF E3DRSP_Window_RectangleF(E3DRSP_Window window)
{
	auto rectangle = static_cast<Window*>(window)->RectangleF();
	E3DRSP_RectangleF r = {rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height};
	return r;
}

E3DRSP_Rectangle E3DRSP_Window_Rectangle(E3DRSP_Window window)
{
	auto rectangle = static_cast<Window*>(window)->Rectangle();
	E3DRSP_Rectangle r = {rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height};
	return r;
}

bool E3DRSP_Window_IsFocused(E3DRSP_Window window)
{
	return static_cast<Window*>(window)->IsFocused();
}

void E3DRSP_Window_SetMousePosition(E3DRSP_Window window, const E3DRSP_Point* p)
{
	static_cast<Window*>(window)->SetMousePosition(Point{p->X, p->Y});
}

void E3DRSP_Window_SetTitle(E3DRSP_Window window, const char* title)
{
	static_cast<Window*>(window)->SetTitle(title);
}

void E3DRSP_Window_Destroy(E3DRSP_Window window)
{
	delete static_cast<Window*>(window);
}
