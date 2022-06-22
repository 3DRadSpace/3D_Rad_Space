#include "ObjectEditorDialog.hpp"

using namespace Engine3DRadSpace;

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, HWND owner, IObjectEditorWindow* objectType) :
	_hInstance(hInstance),
	_window(nullptr),
	_owner(owner),
	_objectType(objectType),
	_globalInstance(nullptr)
{
	this->_hGlobal = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if(this->_hGlobal == nullptr)
		throw ResourceCreationException("Cannot allocate memory for the object editor dialog!", typeid(ObjectEditorDialog));
	
	this->_dialogTemplate = (LPDLGTEMPLATE)GlobalLock(this->_hGlobal);
	if(this->_dialogTemplate == nullptr)
		throw ResourceCreationException("Failed to lock memory handle!",typeid(ResourceCreationException));
	
	this->_dialogTemplate->cdit = 0;
	this->_dialogTemplate->x = 0;
	this->_dialogTemplate->y = 0;
	this->_dialogTemplate->cx = 0;
	this->_dialogTemplate->cy = 0;

	this->_dialogTemplate->style = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME | DS_CENTER;
	this->_dialogTemplate->dwExtendedStyle = 0;

	_templateMemIndex = (LPWORD)(this->_dialogTemplate + 1);

	*_templateMemIndex = 0; //No menu
	*_templateMemIndex = 0; //Default dialog box class

	LPWSTR title = (LPWSTR)_templateMemIndex;
	int titleLen = MultiByteToWideChar(CP_ACP, 0, this->_objectType->GetObjectName(), -1, title, 50);
	*_templateMemIndex += titleLen;
	*_templateMemIndex++ = 0; //No elements

	GlobalUnlock(this->_hGlobal);

	this->_globalInstance = this;
}

int ObjectEditorDialog::ShowDialog()
{
	return DialogBoxIndirectParam(this->_hInstance, this->_dialogTemplate, this->_owner, ObjectEditor_DialogProc, (LPARAM)this);
}

void ObjectEditorDialog::_createForms()
{
	unsigned ax = 10;
	unsigned ay = 10;


}

ObjectEditorDialog* ObjectEditorDialog::GetGlobalInstance()
{
	return this->_globalInstance;
}

HWND ObjectEditorDialog::GetWindow()
{
	return this->_window;
}

ObjectEditorDialog::~ObjectEditorDialog()
{
	for(size_t i = 0; i < this->numControls; i++)
	{
		DestroyWindow(this->_controls[i]);
	}
	GlobalFree(this->_hGlobal);
}

INT_PTR ObjectEditor_DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			ObjectEditorDialog* objectEditor = reinterpret_cast<ObjectEditorDialog*>(lParam);
			objectEditor->_window = hwnd;
			objectEditor->_createForms();
			break;
		}
		default:
			return false;
	}
}
