#pragma once
#include "NumericTextbox.hpp"
#include "../Windows/FindObjectDialog.hpp"
#include <atomic>

class ObjectIDControl : public NumericTextbox
{
	HWND _browseBtn;
	std::atomic<bool> _openedFindWindow;
	Engine3DRadSpace::Objects::ObjectList* _objectList;
	int sx;
	int sy;
public:
	ObjectIDControl(
		HWND owner,
		HINSTANCE hInstance, 
		int x,
		int y,
		int cx, 
		int cy,
		const char* value, 
		Engine3DRadSpace::Objects::ObjectList* list
	);

    virtual void HandleClick(HWND clickedWindow) override;

	int AccX() const noexcept;
	int AccY() const noexcept;
};