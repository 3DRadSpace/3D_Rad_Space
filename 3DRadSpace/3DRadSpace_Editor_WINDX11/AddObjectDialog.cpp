#include "AddObjectDialog.hpp"

AddObjectDialog* AddObjectDialog::GlobalInstance = nullptr;

INT_PTR CALLBACK AddObject_DialogProcess(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_INITDIALOG:
        {
            return true;
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
            return false;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return false;
        }
        //case WM_NCLBUTTONDOWN:
        //{
        //    MessageBeep(0xFFFFFFFF);
        //    return false;
        //}
        case WM_NOTIFY:
        {
            LPNMHDR notif = (LPNMHDR)lparam;
            HWND listview = AddObjectDialog::GlobalInstance->GetListView();
            HWND dialog = AddObjectDialog::GlobalInstance->GetWindow();
            
            if(notif->hwndFrom == listview)
            {
                switch(notif->code)
                {
                    case NM_CLICK:
                    {
                        LPNMITEMACTIVATE item = (LPNMITEMACTIVATE)lparam;
                        switch(21 - item->iItem) //order of ListView items is reversed
                        {
                            //Handle creating objects here.
                            case 0:
                            {
                                break;
                            }
                            default: break;
                        }
                        return true;
                    }
                    default: break;
                }
            }
            return false;
        }
        case WM_SIZE:
        {
            AddObjectDialog::GlobalInstance->Resize();
            return false;
        }
        case WM_CLOSE:
        {
            AddObjectDialog::GlobalInstance->DialogOpen = false;
            EndDialog(AddObjectDialog::GlobalInstance->GetWindow(), LOWORD(IDCANCEL));
            return true;
        }
        default:
            return false;
    }
}

void AddObjectDialog::_createItemForList( __rawstring* name, int imageIndex, int groupIndex)
{
    LVITEM item;
    memset(&item, 0, sizeof(LVITEM));
    item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_GROUPID;
    item.pszText = name;
#ifdef UNICODE
    item.cchTextMax = wcslen(name) + 1;
#else
    item->cchTextMax = strlen(name) + 1;
#endif
    item.iImage = imageIndex;
    item.iGroupId = groupIndex;

    ListView_InsertItem(_listView, &item);
}

void AddObjectDialog::_createGroupForList( wchar_t* name, int index)
{
    LVGROUP group;
    memset(&group, 0, sizeof(LVGROUP));
    group.cbSize = sizeof(LVGROUP);
    group.mask = LVGF_HEADER | LVGF_GROUPID ;
    group.pszHeader = name;
    group.cchHeader = wcslen(name) + 1;
    group.iGroupId = index;

    ListView_InsertGroup(_listView, index, &group);
}

void AddObjectDialog::_insertImage(HBITMAP icon)
{
    int r = ImageList_Add(this->_imageList, icon, nullptr);
    DeleteObject(icon);
}

AddObjectDialog::AddObjectDialog(HINSTANCE hInstance)
{
    this->_hInstance = hInstance;
    this->_dialogWindow = nullptr;
    this->_listView = nullptr;
    this->DialogOpen = false;

    //Allocate memory
    this->hGlobal = GlobalAlloc(GMEM_ZEROINIT, 1024);
    if (this->hGlobal == nullptr)
        throw ResourceCreationException("Failed to initialize memory", typeid(AddObjectDialog));

    this->lpDialogTemplate = (LPDLGTEMPLATE)GlobalLock(this->hGlobal);
    if (this->lpDialogTemplate == nullptr)
        throw ResourceCreationException("Failed to lock memory handle",typeid(AddObjectDialog));

    //Setup dialog layout
    this->lpDialogTemplate->cdit = 0;
    this->lpDialogTemplate->cx = 400;
    this->lpDialogTemplate->cy = 300;
    this->lpDialogTemplate->x = 1;
    this->lpDialogTemplate->y = 1;

    this->lpDialogTemplate->style = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME;//WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION;
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

     _imageList = ImageList_Create(64,64, ILC_COLOR32, 21, 0);

     wchar_t* png = (wchar_t*)L"PNG";

     WORD objectPictures[] =
     {
         IDB_CameraIconPNG ,
         IDB_FPVCameraIconPNG,
         IDB_SourceCodeIconPNG,
         IDB_CSScriptIconPNG,
         IDB_EmptyIconPNG,
         IDB_SkinmeshIconPNG,
         IDB_SkyboxIconPNG,
         IDB_FogIconPNG,
         IDB_RigidbodyIconPNG,
         IDB_GForceIconPNG,
         IDB_ForceIconPNG,
         IDB_GroupIconPNG,
         IDB_SpriteIconPNG,
         IDB_TextPrintIconPNG,
         IDB_SkyColorIconPNG,
         IDB_EOLIconPNG,
         IDB_EOKIconPNG,
         IDB_TimerIconPNG,
         IDB_CounterIconPNG,
         IDB_ExitFadeIconPNG,
         IDB_SoundIconPNG,
         IDB_SoundSourceIconPNG
     };

     size_t l = sizeof(objectPictures) / sizeof(WORD);
     for(size_t i =0 ; i < l; i++)
     {
         _insertImage(loadImgResource(objectPictures[i], png));
     }
     AddObjectDialog::GlobalInstance = this;
}

int AddObjectDialog::ShowDialog(HWND owner)
{
    //Create Dialog Window
    _dialogWindow = CreateDialogIndirect(this->_hInstance, this->lpDialogTemplate, owner, AddObject_DialogProcess, 0);
    if (_dialogWindow == nullptr)
    {
        throw ResourceCreationException("Failed to show the Dialog Window", typeid(AddObjectDialog));
    }

    DialogOpen = true;
    EnableWindow(owner, false);

    //Create the listview control

    _listView = CreateWindow(TEXT("SysListView32"), TEXT(""), WS_VISIBLE | WS_CHILD | LVS_ALIGNTOP, 0, 0, 600, 600, _dialogWindow, nullptr, this->_hInstance, nullptr);

    ListView_EnableGroupView(_listView, true);
    ListView_SetImageList(this->_listView, this->_imageList, LVSIL_NORMAL);

    _createGroupForList((__rawstring*)TEXT("Camera objects"), 0);
    _createGroupForList((__rawstring*)TEXT("Programming"), 1);
    _createGroupForList((__rawstring*)TEXT("3D Visual Objects"), 2);
    _createGroupForList((__rawstring*)TEXT("Physics"), 3);
    _createGroupForList((__rawstring*)TEXT("2D Visual Objects"), 4);
    _createGroupForList((__rawstring*)TEXT("Events"), 5);
    _createGroupForList((__rawstring*)TEXT("Triggereable Objects"), 6);
    _createGroupForList((__rawstring*)TEXT("Sound Objects"), 7);

    _createItemForList((__rawstring*)TEXT("Camera"), 0, 0);
    _createItemForList((__rawstring*)TEXT("First Person Camera"), 1, 0);

    _createItemForList((__rawstring*)TEXT("C++ source"), 2, 1);
    _createItemForList((__rawstring*)TEXT("C# scripts"), 3, 1);
    _createItemForList((__rawstring*)TEXT("Empty"), 4, 1);

    _createItemForList((__rawstring*)TEXT("Skinmesh"), 5, 2);
    _createItemForList((__rawstring*)TEXT("Skybox"), 6, 2);
    _createItemForList((__rawstring*)TEXT("Fog"), 7, 2);

    _createItemForList((__rawstring*)TEXT("Rigidbody"), 8, 3);
    _createItemForList((__rawstring*)TEXT("GForce"), 9, 3);
    _createItemForList((__rawstring*)TEXT("Force"), 10, 3);
    _createItemForList((__rawstring*)TEXT("Group"), 11, 3);

    _createItemForList((__rawstring*)TEXT("Sprite"), 12, 4);
    _createItemForList((__rawstring*)TEXT("TextPrint"), 13, 4);
    _createItemForList((__rawstring*)TEXT("SkyColor"), 14, 4);

    _createItemForList((__rawstring*)TEXT("EventOnLocation"), 15, 5);
    _createItemForList((__rawstring*)TEXT("EventOnKey"), 16, 5);
    _createItemForList((__rawstring*)TEXT("Timer"), 17, 5);
    _createItemForList((__rawstring*)TEXT("Counter"), 18, 5);

    _createItemForList((__rawstring*)TEXT("ExitFade"), 19, 6);

    _createItemForList((__rawstring*)TEXT("SoundEffect"), 20, 7);
    _createItemForList((__rawstring*)TEXT("SoundSource"), 21, 7);

    ShowWindow(this->_dialogWindow, SW_NORMAL);
    ShowWindow(this->_listView, SW_NORMAL);
    Resize();

    MSG msg;
    BOOL validMessage = true;
    while ((validMessage = GetMessage(&msg,this->_dialogWindow, 0, 0)) != FALSE && DialogOpen)
    {
        if(validMessage == -1) throw std::exception("Exception while managing AddObjectDialog messages");

        else if (!IsWindow(this->_dialogWindow) || !IsDialogMessage(this->_dialogWindow, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    EnableWindow(owner, true);
    return IDOK;
}

HWND AddObjectDialog::GetWindow()
{
    return this->_dialogWindow;
}

HWND AddObjectDialog::GetListView()
{
    return this->_listView;
}

void AddObjectDialog::Resize()
{
    RECT r;
    GetClientRect(this->_dialogWindow, &r);
    int w = r.right - r.left;
    int h = r.bottom - r.top;
    SetWindowPos(this->_listView, nullptr, 0, 0, w, h, SWP_SHOWWINDOW);
}

AddObjectDialog::~AddObjectDialog()
{
    DestroyWindow(this->_dialogWindow);
    DestroyWindow(this->_listView);
    ImageList_Destroy(this->_imageList);
    GlobalFree(this->hGlobal);
}
