#include "HelperFunctions.hpp"

int GetTitleBarHeight()
{
	return (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
}

int GetMenuBarHeight()
{
	return GetSystemMetrics(SM_CYMENU);
}
