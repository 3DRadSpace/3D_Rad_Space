#pragma once
#include "IControl.hpp"
#include <Engine3DRadSpace/Content/ContentManager.hpp>

class AssetControl : public IControl
{
protected:
    HWND _label;
    HWND _textBox;
    HWND _button;

    int _cy;
    int _cx;

    Engine3DRadSpace::Content::ContentManager *_content;
public:
    AssetControl(HWND owner, HINSTANCE hInstance, int x, int y, Engine3DRadSpace::Content::ContentManager* content);

    AssetControl(AssetControl&) = default;
    AssetControl &operator=(AssetControl &) = default;

    HWND GetTextbox();
    HWND GetBrowseButton();

    int AccX();
    int AccY();

    unsigned AssetReference;
};

