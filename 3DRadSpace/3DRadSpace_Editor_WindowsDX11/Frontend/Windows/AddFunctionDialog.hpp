#pragma once
#include "../Controls/Dialog.hpp"
#include <Engine3DRadSpace/Reflection/ReflectedObject.hpp>
#include <Engine3DRadSpace/Reflection/ReflectedMemberFunction.hpp>
#include <Engine3DRadSpace/Reflection/Event.hpp>

class AddFunctionDialog : public Dialog
{
	HWND _listFunctions;
	HWND _cancelBtn;
	HWND _okBtn;
public:
	AddFunctionDialog(HWND owner, HINSTANCE hInstance);

	std::optional<Engine3DRadSpace::Reflection::Event> ShowDialog();
};