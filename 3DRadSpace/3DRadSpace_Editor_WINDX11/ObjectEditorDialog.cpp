#include "ObjectEditorDialog.hpp"

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance,LPCSTR object_name,const VisiblePropertiesManager& visibleFields)
{
	this->hGlobal = nullptr;
	this->dlgTemplate = nullptr;
	this->_dlgWindow = nullptr;
	this->result = IDCANCEL;
	this->_hInstance = hInstance;
	this->dlgControls = nullptr;
	

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

	size_t numControls = this->_Fields->GetControlsNum();

	this->dlgControls = new HWND[numControls];

	for(size_t i = 0; i < numControls; )
	{
		switch(this->_Fields->operator[](i).Type)
		{

			case EditableFieldType::Undefined:
				break;
		}
	}

	ShowWindow(this->_dlgWindow, SW_NORMAL);
	
	this->dlgControls = new HWND[this->_Fields->Size() + 2];

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
