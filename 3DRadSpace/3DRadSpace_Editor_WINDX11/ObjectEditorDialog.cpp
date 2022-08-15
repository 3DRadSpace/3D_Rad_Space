#include "ObjectEditorDialog.hpp"

using namespace Engine3DRadSpace;

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, HWND owner, ObjectEditorWindow* objectType, IObject* obj) :
	_hInstance(hInstance),
	_window(nullptr),
	_owner(owner),
	_objectWndInfo(objectType),
	_globalInstance(nullptr),
	_controls(nullptr),
	numControls(0)
{
	this->_hGlobal = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if(this->_hGlobal == nullptr)
		throw ResourceCreationException("Cannot allocate memory for the object editor dialog!", typeid(ObjectEditorDialog));

	this->_dialogTemplate = (LPDLGTEMPLATE)GlobalLock(this->_hGlobal);
	if(this->_dialogTemplate == nullptr)
		throw ResourceCreationException("Failed to lock memory handle!", typeid(ResourceCreationException));

	this->_dialogTemplate->cdit = 0;
	this->_dialogTemplate->x = 0;
	this->_dialogTemplate->y = 0;
	this->_dialogTemplate->cx = this->_objectWndInfo->WindowSize.X;
	this->_dialogTemplate->cy = this->_objectWndInfo->WindowSize.Y;

	this->_dialogTemplate->style = WS_POPUP | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME | DS_CENTER;
	this->_dialogTemplate->dwExtendedStyle = 0;

	_templateMemIndex = (LPWORD)(this->_dialogTemplate + 1);

	*_templateMemIndex = 0; //No menu
	*_templateMemIndex = 0; //Default dialog box class

	std::stringstream titleText;
	titleText << (obj != nullptr ? "Editing" : "Creating") << this->_objectWndInfo->Name << " object";

	LPWSTR title = (LPWSTR)_templateMemIndex;
	int titleLen = MultiByteToWideChar(CP_ACP, 0, titleText.str().c_str(), -1, title, titleText.str().length() + 1);
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

WNDPROC _editProc = nullptr;

void ObjectEditorDialog::_createForms()
{
	size_t i = 0; // _controls[i]
	Point p(10, 10);

	HDC hdc = GetDC(this->_window);

	//create groups
	for(size_t j = 0; j < this->_objectWndInfo->NumGroups; j++)
	{
		Point groupSize = _calculateGroupSize(j);
		_controls[i++] = CreateWindowA(
			"Button",
			this->_objectWndInfo->Groups[j].Name,
			BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
			p.X,
			p.Y,
			groupSize.X,
			groupSize.Y,
			this->_window,
			nullptr,
			this->_hInstance,
			nullptr
		);
		p += groupSize + Point(20, 20);
	}

	p = { 30,30 };
	//create controls
	for(size_t j = 0; j < this->_objectWndInfo->Reflection.Size(); j++)
	{
		const char* visibleName = this->_objectWndInfo->Reflection[j]->GetVisibleName();

		const void* defaultValue = this->_objectWndInfo->Reflection[j]->GetDefaultValue();

		auto CreateLabel = [hdc](HWND owner,HINSTANCE hInstance, int x, int y, const char* text,SIZE &textSize) -> HWND
		{
			GetTextExtentPointA(hdc, text,strlen(text), & textSize);
			
			return CreateWindowA(
				"Static",
				text,
				WS_CHILD | WS_VISIBLE
				, x, y,
				textSize.cx,
				textSize.cy,
				owner,
				nullptr,
				hInstance,
				nullptr
			);
		};

		auto CreateNumericTextbox = [](HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, const char* defValue) -> HWND
		{
			HWND r = CreateWindowA(
				"Edit",
				defValue,
				WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				x,y,cx,cy,
				owner,
				nullptr,
				hInstance,
				nullptr
			);
			if(r == nullptr) throw std::runtime_error(std::string("Failed to create a numeric textbox with default value: ") + defValue);
			_editProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(r, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NumericTextBoxProc)));

			return r;
		};

		switch(Engine3DRadSpace::Reflection::Reflect::TypeDict[this->_objectWndInfo->Reflection[j]->GetFieldType()])
		{
			case 1:
			{
				SIZE textLen{};
				GetTextExtentPointA(hdc, visibleName, strlen(visibleName), &textLen);

				_controls[i++] = CreateWindowA("Button",
					visibleName,
					BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					textLen.cx + GetSystemMetrics(SM_CXMENUCHECK),
					textLen.cy,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				);
				
				p.Y += textLen.cy + 10;
				break;
			}
			case 2:
			{
				SIZE textLen{};
				_controls[i++] = CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textLen
				);

				_controls[i++] = CreateWindowA(
					"EDIT",
					visibleName,
					ES_NUMBER | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
					p.X + textLen.cx + 10,
					p.Y,
					75,
					textLen.cy,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				);

				_controls[i++] = CreateWindowA(
					UPDOWN_CLASSA,
					"",
					UDS_AUTOBUDDY | UDS_ARROWKEYS | UDS_NOTHOUSANDS | UDS_ALIGNRIGHT | WS_VISIBLE | WS_CHILD, //The previous edit element is going to be set as the "buddy"
					0, 0, 0, 0,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				);

				SendMessage(_controls[i - 1], UDM_GETRANGE, 100, 0);
				SendMessage(_controls[i - 1], UDM_SETPOS, 0, std::atoi((char*)defaultValue));

				p.Y += textLen.cy + 10;

				break;
			}
			case 3:
			{
				SIZE textLen{};
				_controls[i++] = CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textLen
				);

				_controls[i++] = CreateNumericTextbox(
					this->_owner,
					this->_hInstance,
					p.X + textLen.cx + 10,
					p.Y,
					75,
					textLen.cy,
					static_cast<const char*>(defaultValue)
				);

				p.Y += textLen.cy + 10;
				break;
			}
			case 4:
			{
				SIZE textLen{};
				//int grpX = 190; // 75 + 75 + 20
				int accX = 0;

				Vector2 defVal = *static_cast<const Vector2*>(defaultValue);

				//groupbox
				_controls[i++] = CreateWindowA(
					"Button",
					visibleName,
					BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					10,
					10,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				);

				//X label and textbox
				_controls[i++] = CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					"X",
					textLen
				);
				accX += textLen.cx + 10;

				_controls[i++] = CreateNumericTextbox(
					this->_owner,
					this->_hInstance,
					p.X + accX,
					p.Y,
					75,
					textLen.cy,
					std::to_string(defVal.X).c_str()
				);
				accX += 75;

				//Y label and textbox
				_controls[i++] = CreateLabel(
					this->_window,
					this->_hInstance,
					p.X + accX,
					p.Y,
					"Y",
					textLen
				);
				accX += textLen.cx + 10;

				_controls[i++] = CreateNumericTextbox(
					this->_owner,
					this->_hInstance,
					p.X + accX,
					p.Y,
					75,
					textLen.cy,
					std::to_string(defVal.Y).c_str()
				);
				accX += 85; // 75 + 10

				SetWindowPos(_controls[i - 3], HWND_BOTTOM, p.X, p.Y, accX + 20, textLen.cy + 40, SWP_SHOWWINDOW | SWP_NOMOVE);

				p.Y += textLen.cy + 10;
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				break;
			}
			case 7:
			{
				break;
			}
			case 8:
			{
				break;
			}
			case 9:
			{
				SIZE textSize{};
				_controls[i++] = CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textSize
				);
				_controls[i++] = CreateWindowA(
					"Edit",
					static_cast<const char*>(defaultValue),
					ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD,
					p.X + textSize.cx + 10,
					p.Y,
					75,
					textSize.cy,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				);
				p.Y += textSize.cy + 10;

				break;
			}
			default:
				break;
		}
	}
}

void ObjectEditorDialog::update_rX(int& x, int newVal)
{
	if(newVal > x)
		x = newVal;
};

Engine3DRadSpace::Point ObjectEditorDialog::_calculateControlSize(const size_t index)
{
	std::type_index t = this->_objectWndInfo->Reflection[index]->GetFieldType();
	const char* visibleName = this->_objectWndInfo->Reflection[index]->GetVisibleName();

	SIZE textSize{}; // sizeof(long) is not always equal to sizeof(int) : Linux x86_64 with GCC : sizeof(int) = 4, sizeof(long) = 8
					 // the C (and C++) standards specify that int is atleast 16 bits long and that long is atleast 32 bits long.
	HDC hdc = GetDC(this->_window);

	switch(Engine3DRadSpace::Reflection::Reflect::TypeDict[t])
	{
		case 1: //bool
		{
			GetTextExtentPointA(hdc, visibleName, strlen(visibleName), &textSize);
			Point s(textSize.cx, textSize.cy); //the function returns a Engine3DRadSpace::Point and not the "struct POINT" that exists in Win32.
			s.X += GetSystemMetrics(SM_CXMENUCHECK); //Size of the checkbox in Windows + spacing between the box and the text.

			return s;
		}
		case 2: //uint8_t,uint16_t,uint32_t,uint64_t
		case 3: //int8_t,int16_t,int32_t,int64_t, float, double, long double
		case 9: //std::string
		case 10: //std::wstring
		{
			GetTextExtentPointA(hdc, visibleName, strlen(visibleName), &textSize);
			Point s(85 + textSize.cx, textSize.cy); // case 2: spacing between label and up down ( 10 ) + UpDown control size (75). 
			return s;								// case 3: spacing between label and textbox ( 10 ) + textbox control size (75).  
		}
		case 4: //2D Vectors
		{
			GetTextExtentPointA(hdc, "X", 1, &textSize);
			Point s(170 + textSize.cx, textSize.cy); //170 =  spacing between the labels and textboxes + lenght of textboxes

			GetTextExtentPointA(hdc, "Y", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		case 5: //3D Vectors
		case 7: //Quaternions (from Euler angles)
		{
			GetTextExtentPointA(hdc, "X", 1, &textSize);
			Point s(255 + textSize.cx, textSize.cy); //255 = spacing between the labels and textboxes + lenght of textboxes

			GetTextExtentPointA(hdc, "Y", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "Z", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		case 6: //4D Vectors
		{
			GetTextExtentPointA(hdc, "X", 1, &textSize);
			Point s(340 + textSize.cx, textSize.cy); //340 = spacing between the labels and textboxes + lenght of textboxes

			GetTextExtentPointA(hdc, "Y", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "Z", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "W", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		case 8:
		{
			GetTextExtentPointA(hdc, "R", 1, &textSize);
			Point s(440 + textSize.cx, textSize.cy); //340 = spacing between the labels and textboxes + lenght of textboxes + button to select color (100)

			GetTextExtentPointA(hdc, "G", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "B", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "A", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		default:
			return { 0,0 };
	}
}

Point ObjectEditorDialog::_calculateGroupSize(size_t index)
{
	Point s = { 30,30 };

	size_t i = 0;
	for(size_t j = 0; j < index; j++)
	{
		i += this->_objectWndInfo->Groups[j].NumFields;
	}

	for(size_t j = 0; j < this->_objectWndInfo->Groups[index].NumFields; j++)
	{
		s += _calculateControlSize(i);
	}

	return s;
}

size_t ObjectEditorDialog::_countControls()
{

	size_t c = 0;
	for(size_t i = 0; i < this->_objectWndInfo->Reflection.Size(); i++)
	{
		switch(Engine3DRadSpace::Reflection::Reflect::TypeDict[this->_objectWndInfo->Reflection[i]->GetFieldType()])
		{
			case 0:
				break;
			case 1:
				c += 1; //checkbox
				break;
			case 2:
				c += 3; //label + edit + updown
			case 9:
			case 10:
				c += 2; // label + textbox
				break;
			case 3:
				c += 2; //label + numeric textbox
				break;
			case 4:
				c += 5; // 1 groupbox + 2 textboxes + 2 labels
				break;
			case 5: //Vector3
			case 7: //Quaternion (we generate rotations from euler angles)
				c += 7; //1 groupbox + 3 textboxes + 3 labels
				break;
			case 6: //Vector4
				c += 9; // 1 groupbox + 4 textboxes + 4 labels
				break;
			case 8:
				c += 10; //1 groupbox + 4 textboxes + 4 labels + 1 button
			default: break;
		}
	}
	c += this->_objectWndInfo->NumGroups;
	return c;
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
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_MENU + 1)); // for some reason COLOR_MENU is the same color as the static's backround color (I'm doing something wrong?)
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

bool _isAllowedFloatCharacter(char c)
{
	return (c >= '0' && c <= '9') ||
		c == '-' ||
		c == '.' ||
		c == ',' ||
		c == VK_RETURN || 
		c == VK_BACK || 
		c == VK_ESCAPE || 
		c == VK_DELETE ||
		c == VK_CONTROL ||
		c == 0x01 ||
		c == 0x03 ||
		c == 0x16 ||
		c == 0x18;
}

LRESULT __stdcall NumericTextBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CHAR:
		{
			char chr = (char)wParam;

			if(_isAllowedFloatCharacter(chr))
			{
				return _editProc(hwnd, msg, wParam, lParam);
			}
			else return MessageBeep(MB_ICONINFORMATION);
		}
		case WM_PASTE:
		{
			BOOL r = OpenClipboard(hwnd);
			if(!r) return 0;

			HANDLE clipboardData = GetClipboardData(CF_OEMTEXT);
			if(clipboardData == nullptr) return 0;

			char* clipboardString = static_cast<char*>(GlobalLock(clipboardData));
			if(clipboardString == nullptr) return 0;

			for(size_t i = 0; i < strlen(clipboardString); i++)
			{
				SendMessage(hwnd, WM_CHAR, clipboardString[i], 0);
			}

			GlobalUnlock(clipboardData);
			CloseClipboard();

			return 1;
		}
		default:
			return _editProc(hwnd, msg, wParam, lParam);
	}
}
