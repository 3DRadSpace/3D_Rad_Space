#include "ObjectEditorDialog.hpp"

ObjectEditorDialog* ObjectEditorDialog::GlobalInstance = nullptr;

ObjectEditorDialog::ObjectEditorDialog(HINSTANCE hInstance, IObjectEditorWindow* object_info) :
	_fields(object_info->GetFields()),
	hGlobal(nullptr),
	dlgTemplate(nullptr),
	_dlgWindow(nullptr),
	result(IDCANCEL),
	_hInstance(hInstance),
	dlgControls(nullptr),
	_objectData(object_info)
{
	ObjectEditorDialog::GlobalInstance = this;

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
	*memTemplateIndex++ = 0; //Predefined window class
	
	int nchar;
	title = (LPWSTR)memTemplateIndex;
	nchar = MultiByteToWideChar(CP_ACP, 0, object_info->GetObjectName(), -1, title, 50);
	memTemplateIndex += nchar;
	*memTemplateIndex++ = 0; //no controls created using CreateDialogIndirectParam

	GlobalUnlock(this->hGlobal);
}

#pragma warning(push)
#pragma warning(disable:6386)
#pragma warning(disable:6385)
int ObjectEditorDialog::ShowDialog(HWND parent)
{
	return DialogBoxIndirectParam(this->_hInstance,this->dlgTemplate,parent, ObjectEditor_DlgProc,reinterpret_cast<LPARAM>(this));
}

void ObjectEditorDialog::CreateDialogForms()
{
	size_t numControls = this->_fields.CountCreatedElements() + 6;
	this->dlgControls = new HWND[numControls];

	size_t numFields = this->_fields.Size();
	this->dlgControls = new HWND[this->_fields.CountHWNDs()];

	unsigned x = 10, y = 10;

	std::vector<__stdstring> Labels = this->_fields.GetTitles();
	std::vector<__stdstring> DefaultValuesList = this->_fields.GetDefaultValues();

	for(size_t i = 0, j = 0, k = 0, l = 0; j < numFields; j++)
	{
		int gh = 0, gw = 0;
		size_t numSubFields = _fields[j].Size();

		switch(_fields[j].Type)
		{
			case EditableFieldType::TextboxesOneLine:
			{
				gw = 110 * numSubFields;
				gh = 50;

				this->dlgControls[i++] = CreateWindow(TEXT("Button"), Labels[k++].c_str(), WS_CHILD | BS_GROUPBOX, x, y, gw, gh, this->_dlgWindow, nullptr, this->_hInstance, nullptr);

				for(size_t k = 0; k < _fields[j].Size(); k++)
				{
					this->dlgControls[i++] = CreateWindow(TEXT("STATIC"), Labels[k++].c_str(), WS_CHILD, x, y + 10, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					this->dlgControls[i++] = CreateWindow(TEXT("EDIT"), DefaultValuesList[l++].c_str(), WS_CHILD, x, y + 30, 100, 22, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					x += 110;
				}
				x = 10;
				break;
			}
			case EditableFieldType::MultilineTextbox:
			{
				gh = 210;
				this->dlgControls[i++] = CreateWindow(TEXT("EDIT"), DefaultValuesList[l++].c_str(), WS_CHILD | ES_MULTILINE, x, y, 100, 200, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				break;
			}
			case EditableFieldType::NumericTextboxes:
			{
				gw = 110 * numSubFields;
				gh = 50;

				this->dlgControls[i++] = CreateWindow(TEXT("Button"), Labels[k++].c_str(), WS_CHILD | BS_GROUPBOX, x, y, gw, gh, this->_dlgWindow, nullptr, this->_hInstance, nullptr);

				for(size_t k = 0; k < _fields[j].Size(); k++)
				{
					this->dlgControls[i++] = CreateWindow(TEXT("STATIC"), Labels[k++].c_str(), WS_CHILD, x, y + 10, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					this->dlgControls[i++] = CreateWindow(TEXT("EDIT"), DefaultValuesList[l++].c_str(), WS_CHILD | ES_NUMBER, x, y + 30, 100, 22, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					x += 110;
				}
				x = 10;
				break;
			}
			case EditableFieldType::UpDowns:
			{
				gw = 110 * numSubFields;
				gh = 50;
				this->dlgControls[i++] = CreateWindow(TEXT("Button"), Labels[k++].c_str(), WS_CHILD | BS_GROUPBOX, x, y, gw, gh, this->_dlgWindow, nullptr, this->_hInstance, nullptr);

				for(size_t k = 0; k < _fields[j].Size(); k++)
				{
					this->dlgControls[i++] = CreateWindow(TEXT("STATIC"), Labels[k++].c_str(), WS_CHILD, x, y + 10, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					this->dlgControls[i] = CreateWindow(UPDOWN_CLASS, NULL, WS_CHILD, x, y + 30, 100, 22, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
					SendMessage(this->dlgControls[i], UDM_SETPOS32, 0, static_cast<int>(std::stof(DefaultValuesList[l++])));
					SendMessage(this->dlgControls[i], UDM_SETRANGE32, static_cast<int>(std::stof(DefaultValuesList[l++])), static_cast<int>(std::stof(DefaultValuesList[l++])));
					i++;
					x += 110;
				}
				x = 10;
				break;
			}
			case EditableFieldType::Color:
			{
				this->dlgControls[i++] = CreateWindow(TEXT("Button"), Labels[k++].c_str(), WS_CHILD | BS_GROUPBOX, x, y, 350, 50, this->_dlgWindow, nullptr, this->_hInstance, nullptr);

				this->dlgControls[i++] = CreateWindow(TEXT("Button"), TEXT("Red"), WS_CHILD, x + 5, y + 10, 50, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				this->dlgControls[i++] = CreateWindow(TEXT("Button"), TEXT("Green"), WS_CHILD, x + 110, y + 10, 50, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				this->dlgControls[i++] = CreateWindow(TEXT("Button"), TEXT("Blue"), WS_CHILD, x + 210, y + 10, 50, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);

				this->dlgControls[i] = CreateWindow(UPDOWN_CLASS, nullptr, WS_CHILD, x, y + 30, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				SendMessage(this->dlgControls[i], UDM_SETRANGE32, 0, 255);
				i++;

				this->dlgControls[i] = CreateWindow(UPDOWN_CLASS, nullptr, WS_CHILD, x + 110, y + 30, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				SendMessage(this->dlgControls[i], UDM_SETRANGE32, 0, 255);
				i++;

				this->dlgControls[i] = CreateWindow(UPDOWN_CLASS, nullptr, WS_CHILD, x + 220, y + 30, 100, 25, this->_dlgWindow, nullptr, this->_hInstance, nullptr);
				SendMessage(this->dlgControls[i], UDM_SETRANGE32, 0, 255);
				i++;
				break;
			}
			case EditableFieldType::Key:
			{
				//not sure if I'm going to use a "Hotkey" control.
				break;
			}
			case EditableFieldType::MultipleKeys:
			{
				//Same thing here
				break;
			}
			default: break;
		}
		y += gh;
	}
	ShowWindow(this->_dlgWindow, SW_NORMAL);
}

#pragma warning(pop)

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

INT_PTR CALLBACK ObjectEditor_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			ObjectEditorDialog* oed = reinterpret_cast<ObjectEditorDialog*>(lParam);
			oed->_dlgWindow = hwnd;
			oed->CreateDialogForms();
			return true;
		}
		case WM_COMMAND:
			return false;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
			return false;
		}
		case WM_CLOSE:
			EndDialog(hwnd, LOWORD(IDCANCEL));
			return true;
		default: break;
	}
	return true;
}