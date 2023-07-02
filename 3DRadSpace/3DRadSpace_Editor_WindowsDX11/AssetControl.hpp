#pragma once
#include "IControl.hpp"

class AssetControl :
    public IControl
{
protected:
    HWND _label;
    HWND _textBox;
    HWND _button;

    int _cy;
public:
    AssetControl(HWND owner, HINSTANCE hInstance, int x, int y);

    AssetControl(AssetControl&) = default;
    AssetControl &operator=(AssetControl &) = default;

    HWND GetTextbox();
    HWND GetBrowseButton();
};

