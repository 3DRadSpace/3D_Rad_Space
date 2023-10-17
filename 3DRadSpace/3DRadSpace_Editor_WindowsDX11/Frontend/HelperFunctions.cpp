#include "HelperFunctions.hpp"
#include <codecvt>
#include <locale>
#include <filesystem>

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
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0) + sizeof(L'\00');
	std::unique_ptr<wchar_t[]> ws = std::make_unique<wchar_t[]>(len);
	memset(ws.get(), 0, sizeof(wchar_t) * len);
	
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, ws.get(), len);
	std::wstring r(ws.get());
	return r;
}

std::string GetExecutablePath()
{
	auto len = GetCurrentDirectoryA(0, nullptr);
	std::unique_ptr<char[]> path = std::make_unique<char[]>(len);
	GetCurrentDirectoryA(len, path.get());
	return std::string(path.get());
}