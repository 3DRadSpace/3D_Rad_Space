#pragma once
#include "IControl.hpp"
#include <Engine3DRadSpace/Reflection/Event.hpp>

class EventControl : public IControl
{
	Engine3DRadSpace::Reflection::Event* _event;
	Engine3DRadSpace::Objects::ObjectList* _list;

	HWND _groupBox;
	HWND _btnAddCall;
	HWND _btnRemoveCall;

	int _cx;
	int _cy;

	std::atomic<bool> _findFunction;
public:
	EventControl(
		HWND owner,
		HINSTANCE hInstance,
		int x,
		int y,
		Engine3DRadSpace::Reflection::Event* event,
		Engine3DRadSpace::Objects::ObjectList* list
	);

	void HandleClick(HWND clickedWindow) override;

	int AccX() const noexcept;
	int AccY() const noexcept;

	Engine3DRadSpace::Reflection::Event& GetEvent() const noexcept;

	~EventControl() override = default;
};