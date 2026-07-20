#include "ObjectIDControl.hpp"

ObjectIDControl::ObjectIDControl(
	HWND owner,
	HINSTANCE hInstance,
	int x, 
	int y,
	int cx,
	int cy, 
	const char* value,
	Engine3DRadSpace::Objects::ObjectList* list
) :
	NumericTextbox(owner, hInstance, x, y, cx, cy, value),
	_openedFindWindow(false),
	_objectList(list)
{
	SIZE size{};
	GetTextExtentPointA(GetDC(owner), "...", 3, &size);

	sx = size.cx + 5;
	sy = size.cy + 7;

	_browseBtn = CreateWindowExA(
		0,
		"Button",
		"...",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x + cx + 5,
		y,
		size.cx + 10,
		size.cy + 7,
		owner,
		nullptr,
		hInstance,
		nullptr
	);
}

void ObjectIDControl::HandleClick(HWND clickedWindow)
{
	if (clickedWindow == _browseBtn && !_openedFindWindow)
	{
		std::thread openFndWindow(
			[this](){
				_openedFindWindow = true;

				FindObjectDialog fod(owner, instance, _objectList);
				auto obj = fod.ShowDialog();
				if (obj.has_value())
				{
					SetWindowTextA(window, std::to_string(obj.value()).c_str());
				}
				_openedFindWindow = false;
			}
		);
		openFndWindow.detach();
	}
}

int	ObjectIDControl::AccX() const noexcept
{
	return sx;
}

int ObjectIDControl::AccY() const noexcept
{
	return sy;
}