#pragma once
#include <Windows.h>
#include <Unknwn.h>
#include <windows.h>
#include <gdiplus.h>

#pragma comment(lib,"Gdiplus.lib")

//Functions for random stuff


//GDI

void InitializeGDI();

HBITMAP loadImgResource(wchar_t* pName, wchar_t* pType, HMODULE hInst);

HBITMAP loadImgResource(WORD resNum, LPWSTR pType);

void DeinitializeGDI();