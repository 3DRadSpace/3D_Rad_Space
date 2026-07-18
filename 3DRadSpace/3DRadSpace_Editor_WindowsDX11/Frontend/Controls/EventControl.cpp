#include "EventControl.hpp"
#include "../Windows/AddFunctionDialog.hpp"
#include <Engine3DRadSpace/Objects/Impl/Objects.hpp>
#include <Engine3DRadSpace/Objects/IObject.hpp>
#include <Engine3DRadSpace/Reflection/Event.hpp>
#include <Engine3DRadSpace/Projects/EventRepresentation.hpp>

EventControl::EventControl(
	HWND owner, 
	HINSTANCE hInstance, 
	int x,
	int y, 
	Engine3DRadSpace::Reflection::Event* event,
	Engine3DRadSpace::Objects::ObjectList* list
) : IControl(owner, hInstance),
	_event(event),
	_list(list)
{
	HDC hdc = GetDC(owner);

	SIZE textSize;
	GetTextExtentPoint32A(hdc, "Events", strlen("Events"), &textSize);

	_groupBox = CreateWindowExA(0,
		"BUTTON",
		"Events",
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		x, y, 300, 400,
		owner,
		NULL,
		hInstance,
		NULL
	);

	SIZE sgnTextSize;
	GetTextExtentPoint32A(hdc, "+", 1, &sgnTextSize);

	window = CreateWindowExA(0,
		"ListBox",
		"",
		WS_VISIBLE | WS_CHILD | LBS_NOTIFY,
		x + 10,
		y + textSize.cy + 10,
		260 - sgnTextSize.cx,
		370,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	auto btnPosX = x + 10 + 260 - sgnTextSize.cx;

	_btnAddCall = CreateWindowExA(0,
		"Button",
		"+",
		WS_VISIBLE | WS_CHILD,
		btnPosX,
		y + textSize.cy + 10,
		(2 * sgnTextSize.cx) + 5,
		sgnTextSize.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_btnRemoveCall = CreateWindowExA(0,
		"Button",
		"-", 
		WS_VISIBLE | WS_CHILD,
		btnPosX,
		y + textSize.cy + 10 + sgnTextSize.cy + 5,
		(2 * sgnTextSize.cx) + 5,
		sgnTextSize.cy + 5,
		owner,
		nullptr,
		hInstance,
		nullptr
	);

	_cx = 300;
	_cy = 400;
}

void EventControl::HandleClick(HWND clickedWindow)
{
	if(clickedWindow == _btnAddCall)
	{
		std::thread openFnFinderWindow([this]()
		{
			AddFunctionDialog dialog(this->window, this->instance, this->_list);
			auto event = dialog.ShowDialog();

			if (event.has_value())
			{
				
			}
		});
		openFnFinderWindow.detach();
	}

	if(clickedWindow == _btnRemoveCall)
	{
		
	}
}

int EventControl::AccX() const noexcept
{
	return _cx;
}

int EventControl::AccY() const noexcept
{
	return _cy;
}

Engine3DRadSpace::Reflection::Event& EventControl::GetEvent() const noexcept
{
	return *_event;
}