#include "ObjectEditorDialog.hpp"

/*
using namespace Engine3DRadSpace;

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, HWND owner, IObjectEditorWindow* objectType) :
	_hInstance(hInstance),
	_window(nullptr),
	_owner(owner),
	_objectType(objectType),
	_globalInstance(nullptr),
	_controls(nullptr),
	numControls(0)
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
	this->_dialogTemplate->cx = this->_objectType->GetWindowWidth();
	this->_dialogTemplate->cy = this->_objectType->GetWindowHeight();

	this->_dialogTemplate->style = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME | DS_CENTER;
	this->_dialogTemplate->dwExtendedStyle = 0;

	_templateMemIndex = (LPWORD)(this->_dialogTemplate + 1);

	*_templateMemIndex = 0; //No menu
	*_templateMemIndex = 0; //Default dialog box class

	std::stringstream titleText;
	titleText << (this->_objectType->GameObject ? "Editing" : "Creating") << this->_objectType->GetObjectName() << " object";

	LPWSTR title = (LPWSTR)_templateMemIndex;
	int titleLen = MultiByteToWideChar(CP_ACP, 0, titleText.str().c_str(), -1, title, titleText.str().length()+1);
	*_templateMemIndex += titleLen;
	*_templateMemIndex++ = 0; //No elements

	GlobalUnlock(this->_hGlobal);

	this->_globalInstance = this;

	this->numControls = this->_countControls();
	this->_controls = new HWND[this->numControls];

}

int ObjectEditorDialog::ShowDialog()
{
	return DialogBoxIndirectParam(this->_hInstance, this->_dialogTemplate, this->_owner, ObjectEditor_DialogProc, reinterpret_cast<LPARAM>(this));
}

void ObjectEditorDialog::_createForms()
{

}

void ObjectEditorDialog::update_rX(int& x, int newVal)
{
	if(newVal > x)
		x = newVal;
};

Point ObjectEditorDialog::_calculateGroupSize( size_t index)
{

}

size_t ObjectEditorDialog::_countControls()
{

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
	delete[] this->_controls;
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
			return true;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			return false;
		}
		case WM_CLOSE:
			EndDialog(hwnd, IDCANCEL);
			return true;
		default:
			return false;
	}
}
*/