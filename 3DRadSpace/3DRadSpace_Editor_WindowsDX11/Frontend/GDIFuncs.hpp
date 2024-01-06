#pragma once
#include "../Includes.hpp"

#pragma comment(lib,"Gdiplus.lib")

void InitializeGDI();

HBITMAP loadImgResource(const wchar_t* pName,const wchar_t* pType, HMODULE hInst);
HBITMAP loadImgResource(WORD resNum, LPWSTR pType);

HBITMAP loadImageFromFile(const std::string &path, unsigned &w, unsigned &h);

void DeinitializeGDI();