#include "AddFunctionDialog.hpp"

AddFunctionDialog::AddFunctionDialog(HWND owner, HINSTANCE hInstance) : Dialog(owner, hInstance, nullptr, "")
{

}

std::optional<Engine3DRadSpace::Reflection::Event> AddFunctionDialog::ShowDialog()
{
	return std::nullopt;
}