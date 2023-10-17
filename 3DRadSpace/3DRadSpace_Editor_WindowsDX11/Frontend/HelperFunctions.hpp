#pragma once
#include "GDIFuncs.hpp"
#include <string>

int GetTitleBarHeight();
int GetMenuBarHeight();

std::wstring ConvertToWideString(const std::string& str);
std::string GetExecutablePath();