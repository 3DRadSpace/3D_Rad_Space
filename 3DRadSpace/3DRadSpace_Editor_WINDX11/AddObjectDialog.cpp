#include "AddObjectDialog.hpp"

AddObjectDialog* AddObjectDialog::GlobalInstance = nullptr;

INT_PTR CALLBACK AddObject_DialogProcess(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_INITDIALOG:
        {
            return TRUE;
        }
        case WM_COMMAND:
        {
            switch (LOWORD(wparam))
            {
                case IDOK:
                case IDCANCEL:
                    EndDialog(AddObjectDialog::GlobalInstance->GetWindow(), wparam);
                    break;
            }
            break;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_CLOSE:
        case WM_QUIT:
        {
            AddObjectDialog::GlobalInstance->DialogOpen = false;
            EndDialog(AddObjectDialog::GlobalInstance->GetWindow(), LOWORD(IDCANCEL));
            break;
        }
    }
    return DefWindowProc(hwnd,msg,wparam,lparam);
}

void AddObjectDialog::_createItemForList(LVITEM* item, __rawstring* name, int imageIndex, int groupIndex)
{
    memset(item, 0, sizeof(LVITEM));
    item->mask = LVIF_IMAGE | LVIF_TEXT | LVIF_GROUPID;
    item->pszText = name;
#ifdef UNICODE
    item->cchTextMax = wcslen(name) + 1;
#else
    item->cchTextMax = strlen(name) + 1;
#endif
    item->iImage = imageIndex;
    item->iGroupId = groupIndex;
}

void AddObjectDialog::_createGroupForList(LVGROUP* group, wchar_t* name, int index)
{
    memset(group, 0, sizeof(LVGROUP));
    group->cbSize = sizeof(LVGROUP);
    group->mask = LVGF_HEADER | LVGF_GROUPID;
    group->pszHeader = name;
    group->cchHeader = wcslen(name) + 1;
    group->iGroupId = index;
}

void AddObjectDialog::_insertImage(HICON icon)
{
    ImageList_AddIcon(_hImageListSmall, icon);
    ImageList_AddIcon(_hImageListBig, icon);
    DestroyIcon(icon);
}

AddObjectDialog::AddObjectDialog(HINSTANCE hInstance)
{
    this->_hInstance = hInstance;
    this->_dialogWindow = nullptr;
    this->_listView = nullptr;
    this->DialogOpen = false;

    AddObjectDialog::GlobalInstance = this;

    //Allocate memory
    this->hGlobal = GlobalAlloc(GMEM_ZEROINIT, 1024);
    if (this->hGlobal == nullptr)
        throw ResourceCreationException("Failed to initialize memory", typeid(AddObjectDialog));

    this->lpDialogTemplate = (LPDLGTEMPLATE)GlobalLock(this->hGlobal);
    if (this->lpDialogTemplate == nullptr)
        throw ResourceCreationException("Failed to lock memory handle",typeid(AddObjectDialog));

    //Setup dialog layout
    this->lpDialogTemplate->cdit = 0;
    this->lpDialogTemplate->cx = 200;
    this->lpDialogTemplate->cy = 200;
    this->lpDialogTemplate->x = 1;
    this->lpDialogTemplate->y = 1;

    this->lpDialogTemplate->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION;
    this->lpDialogTemplate->dwExtendedStyle = 0;

    //Setup data that is immediately after the structure
    this->_TemplateMemIndex = (LPWORD)(this->lpDialogTemplate + 1);
    *_TemplateMemIndex++ = 0; // No menu
    *_TemplateMemIndex++ = 0; //Predefined dialog class

     //set title
    _title = (LPWSTR)_TemplateMemIndex;
    _nchar = MultiByteToWideChar(CP_ACP, 0, "Add object", -1, this->_title, 50);
    _TemplateMemIndex += _nchar;
    *_TemplateMemIndex++ = 0;

    GlobalUnlock(this->hGlobal);

    _hImageListSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),  ILC_MASK, 3, 0);
    _hImageListBig = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_MASK , 3, 0);

    //HBITMAP icon1 = static_cast<HBITMAP>(LoadImage(_hInstance, MAKEINTRESOURCE(IDB_CameraIconPNG),IMAGE_BITMAP,128,128, LR_DEFAULTCOLOR));
    //HBITMAP icon2 = static_cast<HBITMAP>(LoadImage(_hInstance, MAKEINTRESOURCE(IDB_FPVCameraIconPNG), IMAGE_BITMAP, 128, 128, LR_DEFAULTCOLOR));
    //ImageList_Replace(_hImageList, 0, icon1, nullptr);
    //ImageList_Replace(_hImageList, 1, icon2, nullptr);

    //TODO: FIND A WAY TO FIX THE ICONS

    this->_insertImage(static_cast<HICON>(LoadIcon(_hInstance, MAKEINTRESOURCE(IDB_CameraIconPNG))));
    this->_insertImage(static_cast<HICON>(LoadIcon(_hInstance, MAKEINTRESOURCE(IDB_FPVCameraIconPNG))));
    this->_insertImage(static_cast<HICON>(LoadIcon(_hInstance, MAKEINTRESOURCE(IDB_SourceCodeIconPNG))));
    
}

int AddObjectDialog::ShowDialog(HWND owner)
{
    //Create Dialog Window
    _dialogWindow = CreateDialogIndirectParam(this->_hInstance, this->lpDialogTemplate, owner, AddObject_DialogProcess, 0);
    if (_dialogWindow == nullptr)
    {
        throw ResourceCreationException("Failed to show the Dialog Window", typeid(AddObjectDialog));
    }

    //Create the listview control

    _listView = CreateWindow(TEXT("SysListView32"), TEXT(""), WS_VISIBLE | WS_CHILD, 0, 0, 400, 400, _dialogWindow, nullptr, this->_hInstance, nullptr);

    ListView_EnableGroupView(_listView, true);
    ListView_SetImageList(this->_listView, this->_hImageListSmall, LVSIL_SMALL);
    ListView_SetImageList(this->_listView, this->_hImageListBig, LVSIL_NORMAL);

    LVGROUP RenderingGroup,ScriptingGroup;
    _createGroupForList(&RenderingGroup, (wchar_t*)L"Rendering", 1);
    _createGroupForList(&ScriptingGroup, (wchar_t*)L"Programming", 2);
    
    ListView_InsertGroup(this->_listView,-1, &RenderingGroup);
    ListView_InsertGroup(this->_listView,2, &ScriptingGroup);

    LVITEM CameraLVI,FPVCameraLVI;
    _createItemForList(&CameraLVI, (__rawstring*)TEXT("Camera"), 0, 1);
    _createItemForList(&FPVCameraLVI, (__rawstring*)TEXT("First Person Camera"), 1, 1);
    
    LVITEM CodeLVI;
    _createItemForList(&CodeLVI, (__rawstring*)TEXT("C++ source"), 2, 2);

    ListView_InsertItem(this->_listView, &CameraLVI);
    ListView_InsertItem(this->_listView, &FPVCameraLVI);
    ListView_InsertItem(this->_listView, &CodeLVI);

    ShowWindow(this->_dialogWindow, SW_NORMAL);
    ShowWindow(this->_listView, SW_NORMAL);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) != 0 && AddObjectDialog::GlobalInstance->DialogOpen)
    {
        if (msg.message == WM_CLOSE || msg.message == WM_QUIT)
            break;
        if (!IsWindow(this->_dialogWindow) || !IsDialogMessage(this->_dialogWindow, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return IDOK;
}

HWND AddObjectDialog::GetWindow()
{
    return this->_dialogWindow;
}

AddObjectDialog::~AddObjectDialog()
{
    GlobalFree(this->hGlobal);
}
