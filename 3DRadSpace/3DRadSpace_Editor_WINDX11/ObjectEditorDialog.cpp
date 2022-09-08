#include "ObjectEditorDialog.hpp"
#include <iostream>

using namespace Engine3DRadSpace;

ObjectEditorDialog* ObjectEditorDialog::_globalInstance = nullptr;

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, HWND owner, ObjectEditorWindow* objectType, IObject* obj) :
	_hInstance(hInstance),
	_window(nullptr),
	_owner(owner),
	_objectWndInfo(objectType),
	_controls(),
	_subclassedControls(),
	_okButton(nullptr),
	_cancelButton(nullptr),
	_helpButton(nullptr),
	_resultObject(obj)
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

	*_templateMemIndex++ = 0; //No menu
	*_templateMemIndex++ = 0; //Default dialog box class

	std::stringstream titleText;
	titleText << (obj != nullptr ? "Editing " : "Creating ") << this->_objectWndInfo->Name << " object";

	LPWSTR title = (LPWSTR)_templateMemIndex;

	int titleLen = MultiByteToWideChar(
		CP_ACP,
		0,
		titleText.str().c_str(),
		-1,
		title,
		(int)titleText.str().length() + 1
	);

	DWORD err = GetLastError();
	_templateMemIndex += titleLen;
	*_templateMemIndex++ = 0; //No elements

	GlobalUnlock(this->_hGlobal);

	this->_globalInstance = this;

	_globalInstance = this;
}

int ObjectEditorDialog::ShowDialog()
{
	int r =  (int)DialogBoxIndirectParamW(this->_hInstance, this->_dialogTemplate, this->_owner, ObjectEditor_DialogProc, reinterpret_cast<LPARAM>(this));
	DWORD err = GetLastError();
	return r;
}

WNDPROC _staticProc = nullptr;

void ObjectEditorDialog::_createForms()
{
	size_t i = 0; // _controls[i]
	Point p(10, 10);

	HDC hdc = GetDC(this->_window);
	int mX = std::numeric_limits<int>::min();

	//create groups
	for(size_t j = 0; j < this->_objectWndInfo->NumGroups; j++)
	{
		Point groupSize = _calculateGroupSize(j);
		if(this->_objectWndInfo->Groups[j].Name != std::string(""))
		{
			_controls.push_back( CreateWindowA(
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
			));
		}
		p.Y += groupSize.Y;
	}
	
	p = { 10,10 };
	//create controls
	for(size_t j = 0; j < this->_objectWndInfo->Reflection.Size(); j++)
	{
		const char* visibleName = this->_objectWndInfo->Reflection[j]->GetVisibleName();

		void* defaultValue = const_cast<void*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue());
		if(this->_resultObject != nullptr)
		{
			defaultValue = ::operator new(this->_objectWndInfo->Reflection[j]->GetFieldSize());
			this->_objectWndInfo->Reflection[j]->ForceGetF(reinterpret_cast<char*>(this->_resultObject), defaultValue);
		}

		auto CreateLabel = [hdc](HWND owner,HINSTANCE hInstance, int x, int y, const char* text,SIZE &textSize) -> HWND
		{
			GetTextExtentPointA(hdc, text,(int)strlen(text), & textSize);
			
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

		auto CreateVector2DControls = [=](size_t &i,Point &p,int &accX)
		{
			SIZE textLen{};
			//int grpX = 190; // 75 + 75 + 20

			Vector2 defVal = *static_cast<const Vector2*>(defaultValue);

			//X label and textbox
			_controls.push_back(CreateLabel(
				this->_window,
				this->_hInstance,
				p.X + 20,
				p.Y + 20,
				"X",
				textLen
			));
			accX += textLen.cx + 30;

			_controls.push_back( NumericTextbox(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				75,
				textLen.cy,
				std::to_string(defVal.X).c_str()
			));
			accX += 75;

			//Y label and textbox
			_controls.push_back( CreateLabel(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				"Y",
				textLen
			));
			accX += textLen.cx + 10;

			_controls.push_back( NumericTextbox(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				75,
				textLen.cy,
				std::to_string(defVal.Y).c_str()
			));
			accX += 85; // 75 + 10
		};

		auto CreateVector3DControls = [=](size_t& i, Point& p,int &accX)
		{
			CreateVector2DControls(i, p, accX);
			SIZE textLen{};

			Vector3 defVal = *static_cast<const Vector3*>(defaultValue);

			//Z label and textbox
			_controls.push_back(CreateLabel(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				"Z",
				textLen
			));
			accX += textLen.cx + 10;

			_controls.push_back(NumericTextbox(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				75,
				textLen.cy,
				std::to_string(defVal.Z).c_str()
			));
			accX += 85; // 75 + 10
		};

		auto CreateVector4DControls = [=](size_t& i, Point& p, int& accX)
		{
			CreateVector3DControls(i, p, accX);
			SIZE textLen{};

			Vector4 defVal = *static_cast<const Vector4*>(defaultValue);

			//Z label and textbox
			_controls.push_back(CreateLabel(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				"W",
				textLen
			));
			accX += textLen.cx + 10;

			_controls.push_back(NumericTextbox(
				this->_window,
				this->_hInstance,
				p.X + accX,
				p.Y + 20,
				75,
				textLen.cy,
				std::to_string(defVal.W).c_str()
			));
			accX += 85; // 75 + 10
		};

		auto CreateUpDown = [=](size_t &i,Point &p, int &accX,int max = 100,int min = 0)
		{
			SIZE textLen{};

			_controls.push_back(CreateWindowA(
				"EDIT",
				visibleName,
				ES_NUMBER | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
				p.X + accX + textLen.cx + 10,
				p.Y,
				75,
				textLen.cy,
				this->_window,
				nullptr,
				this->_hInstance,
				nullptr
			));

			accX += textLen.cx + 10;

			HWND updown = CreateWindowA(
				UPDOWN_CLASSA,
				"",
				UDS_AUTOBUDDY | UDS_ARROWKEYS | UDS_NOTHOUSANDS | UDS_ALIGNRIGHT | WS_VISIBLE | WS_CHILD, //The previous edit element is going to be set as the "buddy"
				0, 0, 0, 0,
				this->_window,
				nullptr,
				this->_hInstance,
				nullptr
			);

			_controls.push_back(updown);
			SendMessage(updown, UDM_GETRANGE, max, min);
			//SendMessage(_controls[i - 1], UDM_SETPOS, 0, std::atoi((char*)defaultValue));

			accX += 75;
		};
		SIZE textLen{};

		switch(Engine3DRadSpace::Reflection::Reflect::TypeDict[this->_objectWndInfo->Reflection[j]->GetFieldType()])
		{
			case Engine3DRadSpace::Reflection::FieldID::Bool:
			{
				GetTextExtentPointA(hdc, visibleName, (int)strlen(visibleName), &textLen);

				HWND checkbox = CreateWindowA("Button",
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
				_controls.push_back(checkbox);

				bool value = *static_cast<const bool*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue());
				SendMessage(checkbox, BM_SETCHECK, value ? BST_CHECKED : BST_UNCHECKED , 0);
				
				p.Y += textLen.cy + 10;
				_update_mX(mX,p.X + textLen.cx + GetSystemMetrics(SM_CXMENUCHECK) + 10);

				break;
			}
			case Engine3DRadSpace::Reflection::FieldID::U8:
			case Engine3DRadSpace::Reflection::FieldID::U16:
			case Engine3DRadSpace::Reflection::FieldID::U32:
			case Engine3DRadSpace::Reflection::FieldID::U64:
			{
				int accX = 0;

				_controls.push_back(CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textLen
				));

				CreateUpDown(i, p, accX);
				p.Y += textLen.cy + 10;
				_update_mX(mX, p.X + accX + 10);

				break;
			}

			case Engine3DRadSpace::Reflection::FieldID::I8:
			case Engine3DRadSpace::Reflection::FieldID::I16:
			case Engine3DRadSpace::Reflection::FieldID::I32:
			case Engine3DRadSpace::Reflection::FieldID::I64:
			case Engine3DRadSpace::Reflection::FieldID::Float:
			case Engine3DRadSpace::Reflection::FieldID::Double:
			case Engine3DRadSpace::Reflection::FieldID::LDouble:
			{
				_controls.push_back(CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textLen
				));

				std::string value("");

				std::unordered_map<std::type_index, int> int_map =
				{
					{typeid(int8_t),1},
					{typeid(int16_t),2},
					{typeid(int32_t),3},
					{typeid(int64_t),4},
					{typeid(float),5},
					{typeid(double),6},
					{typeid(long double),7}
				};

				switch(int_map[this->_objectWndInfo->Reflection[j]->GetFieldType()])
				{
					case 1:
						value = std::to_string(*static_cast<const int8_t*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 2:
						value = std::to_string(*static_cast<const int16_t*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 3:
						value = std::to_string(*static_cast<const int32_t*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 4:
						value = std::to_string(*static_cast<const int64_t*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 5:
						value = std::to_string(*static_cast<const float*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 6:
						value = std::to_string(*static_cast<const double*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					case 7:
						value = std::to_string(*static_cast<const long double*>(this->_objectWndInfo->Reflection[j]->GetDefaultValue()));
						break;
					default:
						break;
				}

				_controls.push_back(NumericTextbox(
					this->_window,
					this->_hInstance,
					p.X + textLen.cx + 10,
					p.Y,
					75,
					textLen.cy,
					value.c_str()
				));

				p.Y += textLen.cy + 10;
				_update_mX(mX, p.X + textLen.cx + 20);
				break;
			}
			
			case Engine3DRadSpace::Reflection::FieldID::Vector2:
			{
				int accX = 0;
				CreateVector2DControls(i, p,accX);

				//groupbox
				_controls.push_back(CreateWindowA(
					"Button",
					visibleName,
					BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					accX + 20,
					textLen.cy + 40,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				));

				_update_mX(mX, p.X + accX + 20);
				p.Y += textLen.cy + 50;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldID::Vector3:
			{
				int accX = 0;
				CreateVector3DControls(i, p, accX);

				_controls.push_back(CreateWindowA(
					"Button",
					visibleName,
					BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					accX + 20,
					textLen.cy + 40,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				));

				_update_mX(mX, p.X + accX + 20);
				p.Y += textLen.cy + 50;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldID::Vector4: //Vector4
			{
				int accX = 0;
				CreateVector4DControls(i, p, accX);

				_controls.push_back(CreateWindowA(
					"Button",
					visibleName,
					BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					accX + 20,
					textLen.cy + 40,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				));

				_update_mX(mX, p.X + accX + 10);
				p.Y += textLen.cy + 50;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldID::Quaternion:
			{
				int accX = 0;
				CreateVector3DControls(i, p, accX);

				_controls.push_back(CreateWindowA(
					"Button",
					visibleName,
					BS_GROUPBOX | WS_CHILD | WS_VISIBLE,
					p.X,
					p.Y,
					accX + 20,
					textLen.cy + 40,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				));

				_update_mX(mX, p.X + accX + 20);
				p.Y += textLen.cy + 50;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldID::RGBAColorNorm:
			{
				int accX = 0;

				_controls.push_back(CreateLabel(
					this->_owner,
					this->_hInstance,
					p.X,
					p.Y,
					"Color",
					textLen
				));
				accX += textLen.cx + 10;

				this->_subclassedControls.push_back(std::unique_ptr<ISubclassedControl>(static_cast<ISubclassedControl*>(new ColorBox(
					this->_hInstance,
					this->_owner,
					p.X + accX,
					p.Y,
					0xFFFFFF,
					textLen.cy,
					textLen.cy
				))));
				_controls.push_back(*this->_subclassedControls[this->_subclassedControls.size() - 1].get());

				accX += textLen.cx + 10;

				_controls.push_back(CreateLabel(
					this->_owner,
					this->_hInstance,
					p.X + accX,
					p.Y,
					"Alpha",
					textLen
				));
				accX += textLen.cx + 10;

				CreateUpDown(i, p, accX, 255, 0);

				_update_mX(mX, p.X + accX + 10);
				p.Y += textLen.cy;

				break;
			}
			
			case Engine3DRadSpace::Reflection::FieldID::String:
			{
				_controls.push_back(CreateLabel(
					this->_window,
					this->_hInstance,
					p.X,
					p.Y,
					visibleName,
					textLen
				));

				_controls.push_back(CreateWindowA(
					"Edit",
					static_cast<std::string*>(defaultValue)->c_str(),
					ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD,
					p.X + textLen.cx + 10,
					p.Y,
					75,
					textLen.cy,
					this->_window,
					nullptr,
					this->_hInstance,
					nullptr
				));
				
				_update_mX(mX, p.X + textLen.cx + 20);
				p.Y += textLen.cy + 10;

				break;
			}
			default:
				break;
		}

		RECT wndRect;
		GetWindowRect(this->_window, &wndRect);

		if((wndRect.bottom - wndRect.top) <= this->_objectWndInfo->WindowSize.Y - 40)
			p.X = mX;

		if(this->_resultObject != nullptr)
			delete defaultValue;
	}

	int btnAccX = 10;
	SIZE textSize;

	GetTextExtentPoint(hdc, TEXT("Help"), 4, &textSize);

	int btnCY = p.Y + 10;

	_helpButton = CreateWindowExW(
		0,
		L"Button",
		L"Help",
		WS_CHILD | WS_VISIBLE,
		btnAccX,
		btnCY,
		textSize.cx + 10,
		textSize.cy + 4,
		this->_window,
		nullptr,
		this->_hInstance,
		nullptr
	);

	RECT wndRect;

	int windowTitleBarAndBorderHeights = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));

	SetWindowPos(this->_window, nullptr, 0, 0, mX + 20, btnCY + textSize.cx + windowTitleBarAndBorderHeights + 10, SWP_NOMOVE);
	GetClientRect(this->_window, &wndRect);
	btnAccX = wndRect.right - textSize.cx - 20;

	GetTextExtentPoint(hdc, TEXT("Ok"), 2, &textSize);
	_okButton = CreateWindow(
		TEXT("Button"),
		TEXT("Ok"),
		BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE,
		btnAccX,
		btnCY,
		textSize.cx + 10,
		textSize.cy + 4,
		this->_window,
		nullptr,
		this->_hInstance,
		nullptr
	);

	
	GetTextExtentPoint(hdc, TEXT("Cancel"), 6, &textSize);
	int btnAccXc = 0;
	btnAccX -= textSize.cx + 20;

	_cancelButton = CreateWindow(
		TEXT("Button"),
		TEXT("Cancel"),
		WS_CHILD | WS_VISIBLE,
		btnAccX,
		btnCY,
		textSize.cx + 10,
		textSize.cy + 4,
		this->_window,
		nullptr,
		this->_hInstance,
		nullptr
	);
}

void _update_mX(int& x, int newVal)
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
		case Engine3DRadSpace::Reflection::FieldID::Bool: //bool
		{
			GetTextExtentPointA(hdc, visibleName, (int)strlen(visibleName), &textSize);
			Point s(textSize.cx, textSize.cy); //the function returns a Engine3DRadSpace::Point and not the "struct POINT" that exists in Win32.
			s.X += GetSystemMetrics(SM_CXMENUCHECK); //Size of the checkbox in Windows + spacing between the box and the text.

			return s;
		}
		case Engine3DRadSpace::Reflection::FieldID::U8:
		case Engine3DRadSpace::Reflection::FieldID::U16:
		case Engine3DRadSpace::Reflection::FieldID::U32:
		case Engine3DRadSpace::Reflection::FieldID::U64:
		case Engine3DRadSpace::Reflection::FieldID::I8:
		case Engine3DRadSpace::Reflection::FieldID::I16:
		case Engine3DRadSpace::Reflection::FieldID::I32:
		case Engine3DRadSpace::Reflection::FieldID::I64:
		case Engine3DRadSpace::Reflection::FieldID::String: //std::string
		{
			GetTextExtentPointA(hdc, visibleName, (int)strlen(visibleName), &textSize);
			Point s(85 + textSize.cx, textSize.cy); // case 2: spacing between label and up down ( 10 ) + UpDown control size (75). 
			return s;								// case 3: spacing between label and textbox ( 10 ) + textbox control size (75).  
		}
		case Engine3DRadSpace::Reflection::FieldID::Vector2:
		{
			GetTextExtentPointA(hdc, "X", 1, &textSize);
			Point s(170 + textSize.cx, textSize.cy); //170 =  spacing between the labels and textboxes + lenght of textboxes

			GetTextExtentPointA(hdc, "Y", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		case Engine3DRadSpace::Reflection::FieldID::Vector3:
		case Engine3DRadSpace::Reflection::FieldID::Quaternion:
		{
			GetTextExtentPointA(hdc, "X", 1, &textSize);
			Point s(255 + textSize.cx, textSize.cy); //255 = spacing between the labels and textboxes + lenght of textboxes

			GetTextExtentPointA(hdc, "Y", 1, &textSize);
			s.X += textSize.cx;

			GetTextExtentPointA(hdc, "Z", 1, &textSize);
			s.X += textSize.cx;

			return s;
		}
		case Engine3DRadSpace::Reflection::FieldID::Vector4:
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
		case Engine3DRadSpace::Reflection::FieldID::RGBAColorNorm:
		{
			GetTextExtentPointA(hdc, "Color", 5, &textSize);
			Point s(20 + textSize.cx, textSize.cy);

			GetTextExtentPointA(hdc, "Alpha", 5, &textSize);
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

ObjectEditorDialog* ObjectEditorDialog::GetGlobalInstance()
{
	return this->_globalInstance;
}

HWND ObjectEditorDialog::GetWindow()
{
	return this->_window;
}

Engine3DRadSpace::IObject* ObjectEditorDialog::GetResultObject()
{
	return this->_resultObject;
}

ObjectEditorDialog::~ObjectEditorDialog()
{
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
		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					ObjectEditorDialog* oed = ObjectEditorDialog::_globalInstance;

					HWND btn = reinterpret_cast<HWND>(lParam);
					if(btn == oed->_okButton)
					{
						if(oed->_resultObject == nullptr)
						{
							oed->_resultObject = oed->_objectWndInfo->CreateEmptyObject();

							int j = 0;
							int k = 0;

							char* entity_ptr = reinterpret_cast<char*>(oed->_resultObject);

							for(size_t i = 0; i < oed->_objectWndInfo->Reflection.Size(); i++)
							{
								switch(Engine3DRadSpace::Reflection::Reflect::TypeDict[oed->_objectWndInfo->Reflection[i]->GetFieldType()])
								{
									case Engine3DRadSpace::Reflection::FieldID::Bool:
									{
										bool value = static_cast<bool>(SendMessage(oed->_controls[j], BM_GETCHECK, 0, 0));
										j++;

										const std::type_info& t = oed->_objectWndInfo->Reflection[i]->GetFieldType();
										oed->_objectWndInfo->Reflection[i]->ForceSetF(
											entity_ptr,
											&value,
											sizeof(bool)
										);
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::U8:
									case Engine3DRadSpace::Reflection::FieldID::U16:
									case Engine3DRadSpace::Reflection::FieldID::U32:
									case Engine3DRadSpace::Reflection::FieldID::U64:
									{
										std::unordered_map<std::type_index, int> uint_map =
										{
											{typeid(uint8_t),1},
											{typeid(uint16_t),2},
											{typeid(uint32_t),3},
											{typeid(uint64_t),4},
										};

										j += 1;

										size_t textLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);

										char* upDownValue = new char[textLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, textLen + 1, reinterpret_cast<LPARAM>(upDownValue));

										switch(uint_map[oed->_objectWndInfo->Reflection[i]->GetFieldType()])
										{
											case 1:
											{
												uint8_t value = *static_cast<const uint8_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());

												if(textLen != 0)
													value = (uint8_t)std::atoi(upDownValue);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(uint8_t));
												break;
											}
											case 2:
											{
												uint16_t value = *static_cast<const uint16_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (uint16_t)std::atoi(upDownValue);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(uint16_t));
												break;
											}
											case 3:
											{
												uint32_t value = *static_cast<const uint32_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (uint32_t)std::atoi(upDownValue);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(uint32_t));
												break;
											}
											case 4:
											{
												uint64_t value = *static_cast<const uint64_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (uint64_t)std::atoll(upDownValue);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(uint32_t));
												break;
											}
											default:
												break;
										}

										delete[] upDownValue;
										j++;
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::I8:
									case Engine3DRadSpace::Reflection::FieldID::I16:
									case Engine3DRadSpace::Reflection::FieldID::I32:
									case Engine3DRadSpace::Reflection::FieldID::I64:
									{
										std::unordered_map<std::type_index, int> int_map =
										{
											{typeid(int8_t),1},
											{typeid(int16_t),2},
											{typeid(int32_t),3},
											{typeid(int64_t),4},
											{typeid(float),5},
											{typeid(double),6},
											{typeid(long double),7}
										};

										j += 1;

										size_t textLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);

										char* editText = new char[textLen + 1];
										memset(editText, 0, textLen + 1);
										SendMessageA(oed->_controls[j], WM_GETTEXT, textLen + 1, reinterpret_cast<LPARAM>(editText));

										switch(int_map[oed->_objectWndInfo->Reflection[i]->GetFieldType()])
										{
											case 1:
											{
												int8_t value = *static_cast<const int8_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (int8_t)std::atoi(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(int8_t));
												break;
											}
											case 2:
											{
												int16_t value = *static_cast<const int16_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (int16_t)std::atoi(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(int16_t));
												break;
											}
											case 3:
											{
												int32_t value = *static_cast<const int32_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (int32_t)std::atol(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(int32_t));
												break;
											}
											case 4:
											{
												int64_t value = *static_cast<const int64_t*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (int64_t)std::atoll(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(int64_t));
												break;
											}
											case 5:
											{
												float value = *static_cast<const float*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = (float)std::atof(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(float));
												break;
											}
											case 6:
											#ifdef _MSC_VER // In MSVC, long double = double
											case 7:
											#endif
											{
												double value = *static_cast<const double*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = std::atof(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(double));
												break;
											}
										#ifndef _MSC_VER //2 Minutes of googling told me that Clang and GCC have sizeof(long double) > sizeof(double)
											case 7:
											{
												long double value = *static_cast<const long double*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
												if(textLen != 0)
													value = std::atolf(editText);

												oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(long double));
												break;
											}
										#endif
											default:
												break;
										}

										SendMessage(oed->_controls[j], WM_GETTEXT, textLen, reinterpret_cast<LPARAM>(editText));

										delete[] editText;
										j++;
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::Vector2:
									{
										Vector2 value = *static_cast<const Vector2*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());

										j += 1; // skip label
										size_t xTxtBoxLen = SendMessageA(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* xTxt = new char[xTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, xTxtBoxLen + 1, reinterpret_cast<LPARAM>(xTxt));

										j += 2; //skip first textbox and second label
										size_t yTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* yTxt = new char[yTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, yTxtBoxLen + 1 , reinterpret_cast<LPARAM>(yTxt));

										if(xTxtBoxLen != 0 && yTxtBoxLen != 0)
											value = Vector2((float)std::atof(xTxt), (float)std::atof(yTxt));

										oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(Vector2));
										delete[] xTxt;
										delete[] yTxt;
										j += 2; // last textbox + groupbox

										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::Vector3:
									{
										Vector3 value = *static_cast<const Vector3*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());

										j += 1; // skip label
										//X coord
										size_t xTxtBoxLen = SendMessageA(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* xTxt = new char[xTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, xTxtBoxLen + 1, reinterpret_cast<LPARAM>(xTxt));

										//Y coordinate
										j += 2;
										size_t yTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* yTxt = new char[yTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, yTxtBoxLen + 1, reinterpret_cast<LPARAM>(yTxt));

										// Z coordinate
										j += 2;
										size_t zTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* zTxt = new char[zTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, zTxtBoxLen + 1, reinterpret_cast<LPARAM>(zTxt));

										if(xTxtBoxLen != 0 && yTxtBoxLen != 0)
											value = Vector3(
												(float)std::atof(xTxt),
												(float)std::atof(yTxt),
												(float)std::atof(zTxt)
											);

										oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(Vector3));
										delete[] xTxt;
										delete[] yTxt;
										delete[] zTxt;
										j += 2;
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::Vector4:
									{
										Vector4 value = *static_cast<const Vector4*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());

										j += 1;
										//X coord
										size_t xTxtBoxLen = SendMessageA(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* xTxt = new char[xTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, xTxtBoxLen + 1, reinterpret_cast<LPARAM>(xTxt));

										//Y coordinate
										j += 2;
										size_t yTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* yTxt = new char[yTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, yTxtBoxLen + 1, reinterpret_cast<LPARAM>(yTxt));

										// Z coordinate
										j += 2;
										size_t zTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* zTxt = new char[zTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, zTxtBoxLen + 1, reinterpret_cast<LPARAM>(zTxt));

										// W coordinate
										j += 2;
										size_t wTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* wTxt = new char[wTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, wTxtBoxLen + 1, reinterpret_cast<LPARAM>(wTxt));

										if(xTxtBoxLen != 0 && yTxtBoxLen != 0)
											value = Vector4(
												(float)std::atof(xTxt),
												(float)std::atof(yTxt),
												(float)std::atof(zTxt),
												(float)std::atof(wTxt)
											);

										oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(Vector4));
										delete[] xTxt;
										delete[] yTxt;
										delete[] zTxt;
										delete[] wTxt;
										j += 2;
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::Quaternion:
									{
										Quaternion value = *static_cast<const Quaternion*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());

										j += 1;
										//X coord
										size_t xTxtBoxLen = SendMessageA(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* xTxt = new char[xTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, xTxtBoxLen + 1, reinterpret_cast<LPARAM>(xTxt));

										//Y coordinate
										j += 2;
										size_t yTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* yTxt = new char[yTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, yTxtBoxLen + 1, reinterpret_cast<LPARAM>(yTxt));

										// Z coordinate
										j += 2;
										size_t zTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* zTxt = new char[zTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, zTxtBoxLen + 1, reinterpret_cast<LPARAM>(zTxt));

										if(xTxtBoxLen != 0 && yTxtBoxLen != 0 && zTxtBoxLen != 0)
											value = Quaternion::CreateFromYawPitchRoll(
												(float)std::atof(yTxt),
												(float)std::atof(xTxt),
												(float)std::atof(zTxt)
											);

										oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(Quaternion));
										delete[] xTxt;
										delete[] yTxt;
										delete[] zTxt;
										j += 2;
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::RGBAColorNorm:
									{
										ColorShader value = *static_cast<const ColorShader*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue());
										j++;

										//color
										COLORREF colorBox = *static_cast<ColorBox*>(oed->_subclassedControls[k].get());
										k++;

										// Alpha
										size_t aTxtBoxLen = SendMessage(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* aTxt = new char[aTxtBoxLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, aTxtBoxLen + 1, reinterpret_cast<LPARAM>(aTxt));

										if(aTxtBoxLen != 0)
											value = ColorShader(
												GetRValue(colorBox) / 255.f,
												GetGValue(colorBox) / 255.f,
												GetBValue(colorBox) / 255.f,
												(float)std::atof(aTxt)
											);

										oed->_objectWndInfo->Reflection[i]->ForceSetF(entity_ptr, &value, sizeof(ColorShader));
										delete[] aTxt;
										j += 2; //skip textbox and button
										break;
									}
									case Engine3DRadSpace::Reflection::FieldID::String:
									{
										std::string* value = nullptr;
										j++;

										size_t txtLen = SendMessageA(oed->_controls[j], WM_GETTEXTLENGTH, 0, 0);
										char* text = new char[txtLen + 1];
										SendMessageA(oed->_controls[j], WM_GETTEXT, txtLen + 1, reinterpret_cast<LPARAM>(text));

										if(txtLen != 0)
										{
											value = new std::string(text); // cursed
											if((*value) != *static_cast<const std::string*>(oed->_objectWndInfo->Reflection[i]->GetDefaultValue()))
											{
												(reinterpret_cast<std::string*>(entity_ptr + oed->_objectWndInfo->Reflection[i]->GetFieldPtr()))->operator=(*value);
											}
										}

										delete value;
										delete[] text;
										j++;
										break;
									}
									default:
										break;
								}
							}
							reinterpret_cast<Engine3DRadSpace::IObject*>(entity_ptr)->Validate();
							EndDialog(hwnd, IDOK);
						}
					}
					if(btn == oed->_helpButton)
					{
						ShellExecuteA(hwnd, nullptr, oed->_objectWndInfo->HelpURLAddress, nullptr, nullptr, SW_NORMAL);
					}
					if(btn == oed->_cancelButton)
					{
						EndDialog(hwnd, IDCANCEL);
					}
					break;
				}
				default:
					break;
			}
			return true;
		}
		case WM_CLOSE:
			EndDialog(hwnd, IDCANCEL);
			return true;
		default:
			return false;
	}
}
