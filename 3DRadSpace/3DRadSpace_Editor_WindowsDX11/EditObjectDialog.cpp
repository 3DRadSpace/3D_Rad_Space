#include "EditObjectDialog.hpp"
#include "NumericTextbox.hpp"
#include "ColorBox.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Reflection;

INT_PTR __stdcall EditObjectDialog_DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static EditObjectDialog* eod = nullptr;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		eod = reinterpret_cast<EditObjectDialog*>(lParam);
		eod->window = hwnd;
		eod->createForms();
		return 1;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 1;
	}
	case WM_COMMAND:
	{
		return 1;
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, IDCANCEL);
		return 1;
	}
	default:
		return 0;
	}
}

void EditObjectDialog::resize()
{

}

EditObjectDialog::EditObjectDialog(HWND owner, HINSTANCE hInstance, ReflectedObject* data, IObject* obj):
	Dialog(owner, hInstance, EditObjectDialog_DlgProc, data->Name + " object"),
	objRefl(data),
	object(obj)
{
	if (data == nullptr) throw std::invalid_argument("data was null");
}

void EditObjectDialog::createForms()
{
	int x = 5;
	int y = 5;

	int k = 0;
	for (auto field : (*objRefl))
	{
		auto setMax = [](int& v, int newValue)
		{
			if (newValue > v) v = newValue;
		};

		int px = x;
		int py = y;

		auto representations = field->Representation();
		for (int j = 0, fOffset = 0; j < representations.size(); j++)
		{
			auto repr = *(representations.begin() + j);

			bool createGroup = field->Representation().size() > 1;
			const char *fieldName = repr.second.c_str();

			//Measure the length of fieldName, in pixels. DPI isn't considered.
			HDC hdc = GetDC(window);
			SIZE fieldNameSize;
			GetTextExtentPointA(hdc, fieldName, int(field->FieldName().length()), &fieldNameSize);

			//creates a Static control (aka Label)
			auto createLabel = [=](const char* text, int &size_x) -> HWND
			{
				SIZE size;
				GetTextExtentPointA(hdc, text, int(field->FieldName().length()), &size);
				size_x = size.cx;

				return CreateWindowExA(
					0,
					"Static",
					text,
					WS_VISIBLE | WS_CHILD,
					px,
					py,
					size.cx + 10,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
			};

			//creates a Edit control (aka TextBox)
			auto createTextbox = [=](const char* defValue) -> HWND
			{
				return CreateWindowExA(
					0,
					"Edit",
					defValue,
					WS_VISIBLE | WS_CHILD,
					px,
					py,
					75,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
			};

			//creates a edit control that only allows numbers
			auto createNumericTextbox = [=](const char* defValue) -> HWND
			{
				return NumericTextbox(window, hInstance, px, py, 75, 25, defValue);
			};

			//creates a browse button, a label and a path textbox.
			auto createFileControls = [&](int x, int y, const char* defPath)
			{
				int sx;
				std::array<HWND, 3> v;

				v[0] = createLabel(fieldName,sx);
				px += sx + 5;

				v[1] = createTextbox(defPath);
				px += 80;

				v[2] = CreateWindowExA(
					0,
					"Button",
					"Browse...",
					WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
					px,
					py,
					50,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
				px += 50;

				return v;
			};
			
			//Value of the field, either from the object that's being edited, or a default value.
			const void* valuePtr = object != nullptr ? field->Get(object) : field->DefaultValue();

			switch (repr.first)
			{
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Boolean:
			{
				int checkBoxLen = GetSystemMetrics(SM_CXMENUCHECK);

				//create a CheckBox
				HWND checkBox = CreateWindowExA(
					0,
					"Button",
					fieldName,
					BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD,
					px,
					py,
					fieldNameSize.cx + 25,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
				windows.push_back(checkBox);

				//send the checkbox state:
				bool value = static_cast<const bool*>(valuePtr);
				SendMessageA(checkBox, BM_SETCHECK, value ? BST_CHECKED : BST_UNCHECKED, 0);

				//update coordinates
				setMax(py, 30);
				px += fieldNameSize.cx + checkBoxLen + 5;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Integer:
			{
				int sx;

				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				//Get signed numeric value.
				int64_t value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(int8_t) :
						value = *reinterpret_cast<const int8_t*>(reinterpret_cast<const char*>(valuePtr) + fOffset );
						fOffset += sizeof(int8_t);
						break;
					case sizeof(int16_t) :
						value = *reinterpret_cast<const int16_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(int16_t);
						break;
					case sizeof(int32_t) :
						value = *reinterpret_cast<const int32_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(int32_t);
						break;
					case sizeof(int64_t) :
						value = *reinterpret_cast<const int64_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(int64_t);
						break;
					default:
						throw std::logic_error("Unknown signed type");
				}
				std::string nstr = std::to_string(value);
				windows.push_back(createNumericTextbox(nstr.c_str())); //create numeric textbox

				px += 80;
				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Unsigned:
			{
				int sx;
				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				//Get unsigned value.
				uint64_t value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(uint8_t) :
						value = *reinterpret_cast<const uint8_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint8_t);
						break;
					case sizeof(uint16_t) :
						value = *reinterpret_cast<const uint16_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint16_t);
						break;
					case sizeof(uint32_t) :
						value = *reinterpret_cast<const uint32_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint32_t);
						break;
					case sizeof(uint64_t) :
						value = *reinterpret_cast<const uint64_t *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint64_t);
						break;
					default:
						throw std::logic_error("Unknown unsigned type!");
				}
				std::string nstr = std::to_string(value);
				windows.push_back(createNumericTextbox(nstr.c_str()));

				px += 80;
				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Float:
			{
				int sx;
				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				double value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(float) :
					case 5: //we're propably dealing with a quaternion.
						value = *reinterpret_cast<const float *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(float);
						break;
					case sizeof(double) :
						value = *reinterpret_cast<const double *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(float);
						break;

					default:
						throw std::logic_error("unknown floating point type");
				}
				std::string nstr = std::to_string(value);
				windows.push_back(createNumericTextbox(nstr.c_str()));

				px += 80;
				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::String:
			{
				int sx;
				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				const std::string value = *static_cast<const std::string*>(field->DefaultValue());
				windows.push_back(createTextbox(value.c_str()));

				px += sx + 5;
				y += 30;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Image:
			{
				const std::string value = *static_cast<const std::string*>(field->DefaultValue());

				HWND pictureBox = CreateWindowExA(
					0,
					"Static",
					"",
					WS_VISIBLE | WS_CHILD | SS_BITMAP,
					px,
					py,
					50,
					50,
					window,
					nullptr,
					hInstance,
					nullptr
				);
				windows.push_back(pictureBox);

				HBITMAP image = LoadBitmapA(nullptr, value.c_str());
				SendMessageA(pictureBox, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(image));

				createFileControls(x, y, value.c_str());

				setMax(py, 200);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Model:
			{
				const std::string value = *static_cast<const std::string*>(valuePtr);
				createFileControls(px, py, value.c_str());
				//create preview button

				windows.push_back(
					CreateWindowExA(
						0,
						"Button",
						"Preview",
						BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
						x,
						y,
						50,
						25,
						window,
						nullptr,
						hInstance,
						nullptr
					)
				);

				px = x + 200;
				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Key:
			{
				int sx;
				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				HWND hotkey = CreateWindowExA(
					0,
					HOTKEY_CLASSA,
					"",
					WS_CHILD | WS_VISIBLE,
					px,
					py,
					75,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);

				windows.push_back(hotkey);

				auto key = static_cast<const Engine3DRadSpace::Input::Key*>(valuePtr);
				SendMessageA(hotkey, HKM_SETHOTKEY, static_cast<WPARAM>(LOBYTE(key)), 0);

				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Enum:
			{
				int sx;
				windows.push_back(createLabel(fieldName, sx));
				px += sx + 5;

				//TODO: Create a combo box with all enum types

				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Color:
			{
				int sx;
				Color color = *static_cast<const Color*>(valuePtr);

				createLabel("Alpha", sx);
				px += sx;

				std::string alphaStr = std::to_string(color.A);
				windows.push_back(createTextbox(alphaStr.c_str()));
				px += 80;

				windows.push_back(ColorBox(window, hInstance,px,py,25,25, color));
				px += 30;
				setMax(py, 30);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Custom:
			{
				break;
			}
			default:
				break;
			}

			if (createGroup)
			{
				CreateWindowExA(
					0,
					"Button",
					field->FieldName().c_str(),
					BS_GROUPBOX | WS_VISIBLE | WS_CHILD,
					x,
					y,
					px - x + 10,
					py - y + 10,
					window,
					nullptr,
					hInstance,
					nullptr
				);
			}
			px = x;
		}
		y = py;
	}

	SetWindowPos(window, nullptr, 0, 0, 400, 400, SWP_NOMOVE);
}

Engine3DRadSpace::IObject* EditObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(this);
	if (r == IDOK)
	{
		return nullptr;
	}
	else return nullptr;
}

EditObjectDialog::~EditObjectDialog()
{
	for (HBITMAP bitmap : images)
	{
		DeleteObject(bitmap);
	}
}