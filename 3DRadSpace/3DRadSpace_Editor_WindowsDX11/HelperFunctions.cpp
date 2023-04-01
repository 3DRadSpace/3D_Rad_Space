#include "HelperFunctions.hpp"
#include <codecvt>
#include <locale>

int GetTitleBarHeight()
{
	return (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
}

int GetMenuBarHeight()
{
	return GetSystemMetrics(SM_CYMENU);
}

std::wstring ConvertToWideString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), nullptr, 0);
	wchar_t* ws = new wchar_t[len];
	memset(ws, 0, sizeof(wchar_t) * len);
	
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), ws, len);
	std::wstring r(ws);
	delete[] ws;
	return r;
}
