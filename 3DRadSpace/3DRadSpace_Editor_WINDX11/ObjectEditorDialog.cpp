#include "ObjectEditorDialog.hpp"


ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, const char* object_name,const EditableFieldCollection &visibleFields):
	_fields(visibleFields),hGlobal(nullptr),dlgTemplate(nullptr),_dlgWindow(nullptr),result(IDCANCEL),_hInstance(hInstance),dlgControls(nullptr)
{	
	this->hGlobal = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if(this->hGlobal == nullptr)
		throw Engine3DRadSpace::ResourceCreationException("Failed to allocate memory", typeid(ObjectEditorDialog));

	dlgTemplate = (LPDLGTEMPLATE)GlobalLock(this->hGlobal);
	if(dlgTemplate == nullptr)
		throw Engine3DRadSpace::ResourceCreationException("Failed to lock memory to the main thread!", typeid(ObjectEditorDialog));

	LPWSTR title;
	LPWORD memTemplateIndex;

	memTemplateIndex = (LPWORD)(dlgTemplate + 1);
	*memTemplateIndex++ = 0; //No menu
	*memTemplateIndex++ = 0;//Predefined window class
	
	int nchar;
	title = (LPWSTR)memTemplateIndex;
	nchar = MultiByteToWideChar(CP_ACP, 0, object_name, -1, title, 50);
	memTemplateIndex += nchar;
	*memTemplateIndex++ = 0; //no controls created using CreateDialogIndirectParam

	GlobalUnlock(this->hGlobal);
}

int ObjectEditorDialog::ShowDialog(HWND parent)
{
	this->_dlgWindow = CreateDialogIndirectParam(this->_hInstance, this->dlgTemplate, parent, nullptr, 0);
	if(this->dlgTemplate == nullptr)
	{
		throw Engine3DRadSpace::ResourceCreationException("Failed to create the object editor dialog!", typeid(ObjectEditorDialog));
	}

	size_t numControls = this->_fields.CountCreatedElements() + 6;
	this->dlgControls = new HWND[numControls];

	ShowWindow(this->_dlgWindow, SW_NORMAL);

	size_t numFields = this->_fields.Size();
	this->dlgControls = new HWND[2*this->_fields.CountCreatedElements() + numFields];

	unsigned x = 10, y = 10;

	for(size_t i = 0, j = 0; j < numFields; )
	{	
		int gh = 0, gw = 0;
		switch(_fields[j].Type)
		{
			case EditableFieldType::TextboxesOneLine:
			{
				this->dlgControls[i] = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD | BS_GROUPBOX, x, y, gw, gh, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				
				for(size_t k = 0; k < _fields[j].Size(); k++)
				{
					this->dlgControls[i++] = CreateWindow(TEXT("STATIC"), TEXT(""), WS_CHILD, x, y, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					this->dlgControls[i++] = CreateWindow(TEXT("EDIT"), nullptr, WS_CHILD, x, y + 30, 100, 22, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					x += 110;
				}
				break;
			}
			default: break;
		}
		j++;
	}

	MSG msg;
	BOOL validMessage;
	while((validMessage = GetMessage(&msg, this->_dlgWindow, 0, 0)) != 0)
	{
		if(!IsWindow(this->_dlgWindow) || !IsDialogMessage(this->_dlgWindow, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return IDOK;
}

HINSTANCE ObjectEditorDialog::GetHINSTANCE()
{
	return this->_hInstance;
}

HWND ObjectEditorDialog::GetDialogWindow()
{
	return this->_dlgWindow;
}

ObjectEditorDialog::~ObjectEditorDialog()
{
	DestroyWindow(this->_dlgWindow);
	GlobalFree(this->hGlobal);
}
