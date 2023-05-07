#pragma once
#include "IControl.hpp"
#include <Engine3DRadSpace/Color.hpp>
#include <array>

class ColorBox : public IControl
{
	Engine3DRadSpace::Color color;
	HBRUSH brush;
	static WNDPROC staticProc;
	std::array<COLORREF,16> customColors;
public:
	ColorBox(HWND owner, HINSTANCE hInstance,int x, int y, int cx, int cy, Engine3DRadSpace::Color color);

	/// <summary>
	/// Opens the color dialog box.
	/// </summary>
	void SetColor();
	/// <summary>
	/// Sets a defined color.
	/// </summary>
	/// <param name="color">Color. Only R, G, B components are used.</param>
	void SetColor(Engine3DRadSpace::Color color);
	Engine3DRadSpace::Color GetColor();

	~ColorBox();

	friend LRESULT WINAPI ColorBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

