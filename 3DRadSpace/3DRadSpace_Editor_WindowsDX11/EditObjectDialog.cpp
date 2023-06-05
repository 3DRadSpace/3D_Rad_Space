#include "EditObjectDialog.hpp"
#include "NumericTextbox.hpp"
#include "ColorBox.hpp"
#include <Engine3DRadSpace/IObject.hpp>
#include <Engine3DRadSpace/Logging/ResourceLoadingError.hpp>
#include "EditorWindow.hpp"

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
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW ));
		EndPaint(hwnd, &ps);
		return 1;
	}
	case WM_COMMAND:
	{
		switch(HIWORD(wParam))
		{
			case BN_CLICKED:
			{
				if(lParam == reinterpret_cast<LPARAM>(eod->okButton))
				{
					if(eod->setObject())
						EndDialog(hwnd, IDOK);
				}
				if(lParam == reinterpret_cast<LPARAM>(eod->cancelButton))
				{
					EndDialog(hwnd, IDCANCEL);
				}
				return 1;
			}
			default:
				return 0;
		}
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

EditObjectDialog::EditObjectDialog(HWND owner, HINSTANCE hInstance, ReflectedObject* data, IObject* obj):
	Dialog(owner, hInstance, EditObjectDialog_DlgProc, data->Name + " object"),
	objRefl(data),
	object(obj),
	helpButton(nullptr),
	okButton(nullptr),
	cancelButton(nullptr)
{
	if (data == nullptr) throw std::invalid_argument("data was null");
}

void EditObjectDialog::createForms()
{
	int x = 5;
	int y = 10;

	HDC hdc = GetDC(window);
	int windowWidth = x;

	for (auto field : (*objRefl))
	{
		auto setMax = [](int& v, int newValue)
		{
			if (newValue > v) v = newValue;
		};

		int px = x;
		int inc_y = 0;

		bool createGroup = field->Representation().size() > 1;

		//create a group if the field is a quaternion.
		if(createGroup == false) createGroup = field->Representation()[0].first == FieldRepresentationType::Quaternion;

		//Measure the length of fieldName, in pixels. DPI isn't considered.
		SIZE fieldNameSize;
		GetTextExtentPointA(hdc, field->FieldName().c_str(), int(field->FieldName().length()), &fieldNameSize);
		int textboxHeight = fieldNameSize.cy + 2;

		//Createa a group if necessary
		HWND currentGroup = nullptr;
		if(createGroup)
		{
			currentGroup = CreateWindowExA(
				0,
				"Button",
				field->FieldName().c_str(),
				BS_GROUPBOX | WS_VISIBLE | WS_CHILD,
				x,
				y,
				10,
				10,
				window,
				nullptr,
				hInstance,
				nullptr
			);

			px += 10;
			y += textboxHeight;
		}

		auto representations = field->Representation();
		for (int j = 0, fOffset = 0; j < representations.size(); j++)
		{
			auto& repr = *(representations.begin() + j);
			std::string fieldName = repr.second.empty() ? field->FieldName() : repr.second;

			//creates a Static control (aka Label)
			auto createLabel = [&](const char* text, int &size_x) -> HWND
			{
				SIZE size;
				GetTextExtentPointA(hdc, text, int(strlen(text)), &size);
				
				size_x = size.cx;
				return CreateWindowExA(
					0,
					"Static",
					text,
					WS_VISIBLE | WS_CHILD,
					px,
					y,
					size.cx + 10,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
			};

			//creates a Edit control (aka TextBox)
			auto createTextbox = [&](const char* defValue) -> HWND
			{
				return CreateWindowExA(
					0,
					"Edit",
					defValue,
					WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
					px,
					y,
					75,
					textboxHeight,
					window,
					nullptr,
					hInstance,
					nullptr
				);
			};

			//creates a edit control that only allows numbers
			auto createNumericTextbox = [&](const char* defValue) -> HWND
			{
				return NumericTextbox(window, hInstance, px, y, 75, textboxHeight, defValue);
			};

			//creates a browse button, a label and a path textbox.
			auto createFileControls = [&](int x, int y, const char* defPath)
			{
				int sx;
				HWND pathTextbox;

				createLabel(fieldName.c_str(), sx);
				px += sx + 5;

				pathTextbox = createTextbox(defPath);
				px += 80;

				CreateWindowExA(
					0,
					"Button",
					"Browse...",
					WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
					px,
					y,
					50,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
				px += 50;

				return pathTextbox;
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
					fieldName.c_str(),
					BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD,
					px,
					y,
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
				setMax(inc_y, 30);
				px += fieldNameSize.cx + checkBoxLen + 5;
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Integer:
			{
				int sx;

				createLabel(fieldName.c_str(), sx);
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
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Unsigned:
			{
				int sx;
				createLabel(fieldName.c_str(), sx);
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
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Float:
			{
				int sx;
				createLabel(fieldName.c_str(), sx);
				px += sx + 5;

				double value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(float) :
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
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Quaternion:
			{
				//read value
				auto q = *reinterpret_cast<const Engine3DRadSpace::Math::Quaternion *>(reinterpret_cast<const char *>(valuePtr) + fOffset);
				auto eulerAngles = q.ToYawPitchRoll();

				auto pitch = std::to_string(eulerAngles.X);
				auto yaw = std::to_string(eulerAngles.Y);
				auto roll = std::to_string(eulerAngles.Z);

				int sx;
				//Euler angles X field
				createLabel("X", sx);
				px += sx + 5;
				windows.push_back(createNumericTextbox(pitch.c_str()));
				px += 80;

				//Euler angles Y field
				createLabel("Y", sx);
				px += sx + 5;
				windows.push_back(createNumericTextbox(yaw.c_str()));
				px += 80;

				//Euler angles Z field
				createLabel("Z", sx);
				px += sx + 5;
				windows.push_back(createNumericTextbox(pitch.c_str()));
				px += 80;
				
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::String:
			{
				int sx;
				createLabel(fieldName.c_str(), sx);
				px += sx + 5;

				const std::string value = *static_cast<const std::string*>(field->DefaultValue());
				windows.push_back(createTextbox(value.c_str()));

				px += sx + 5;
				setMax(inc_y, textboxHeight + 5);
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
					y,
					50,
					50,
					window,
					nullptr,
					hInstance,
					nullptr
				);

				HBITMAP image = LoadBitmapA(nullptr, value.c_str());
				SendMessageA(pictureBox, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(image));

				windows.push_back(createFileControls(x, y + 200, value.c_str()));

				setMax(inc_y, 205 + textboxHeight);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Model:
			{
				const std::string value = *static_cast<const std::string*>(valuePtr);
				windows.push_back(createFileControls(px, y, value.c_str()));
				
				//create preview button
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
				);

				px = x + 30;
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Key:
			{
				int sx;
				createLabel(fieldName.c_str(), sx);
				px += sx + 5;

				HWND hotkey = CreateWindowExA(
					0,
					HOTKEY_CLASSA,
					"",
					WS_CHILD | WS_VISIBLE,
					px,
					y,
					75,
					25,
					window,
					nullptr,
					hInstance,
					nullptr
				);
				px += 80;

				windows.push_back(hotkey);

				auto key = static_cast<const Engine3DRadSpace::Input::Key*>(valuePtr);
				SendMessageA(hotkey, HKM_SETHOTKEY, static_cast<WPARAM>(LOBYTE(key)), 0);

				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Enum:
			{
				int sx;
				createLabel(fieldName.c_str(), sx);
				px += sx + 5;
				//TODO: Create a combo box with all enum types

				setMax(inc_y, textboxHeight + 5);
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

				windows.push_back(ColorBox(window, hInstance,px,y,25,25, color));
				px += 30;
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case Engine3DRadSpace::Reflection::FieldRepresentationType::Custom:
			{
				break;
			}
			default:
				break;
			}
		}

		if(currentGroup != nullptr)
		{
			SetWindowPos(currentGroup, nullptr, 0, 0, px - x, inc_y + textboxHeight + 5, SWP_NOMOVE);
			y += textboxHeight;
		}

		setMax(windowWidth, px + 20);
		px = x;
		y += inc_y;
	}

	int titleBarHeight = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER);
	int height = y + 3 * titleBarHeight;
	SetWindowPos(window, nullptr, 0, 0, windowWidth, height, SWP_NOMOVE);

	SIZE size;
	GetTextExtentPoint32A(hdc, "Help", 4, &size);

	int buttonHeight = y + 10;

	helpButton = CreateWindowExA(
		0,
		"Button",
		"Help",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	GetTextExtentPoint32A(hdc, "Cancel", 6, &size);
	
	int okButtonX = windowWidth - size.cx - 30;
	okButton = CreateWindowExA(
		0,
		"Button",
		"OK",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		okButtonX,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);

	cancelButton = CreateWindowExA(
		0,
		"Button",
		"Cancel",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		okButtonX - size.cx - 10,
		buttonHeight,
		size.cx + 10,
		size.cy + 7,
		window,
		nullptr,
		hInstance,
		nullptr
	);
}

bool EditObjectDialog::setObject()
{
	int i = 0;
	for(auto field : *objRefl)
	{
		int structSize = static_cast<int>(field->TypeSize());
		std::unique_ptr<uint8_t[]> newStruct = std::make_unique<uint8_t[]>(structSize);
		int j = 0;
		char text[256] = {0};

		auto graphicsDevice = object != nullptr ? object->GetGraphicsDeviceHandle() : gEditorWindow->GetGraphicsDevice();
		
		if(object == nullptr)
			object = objRefl->CreateBlankObject();

		for(auto repr : field->Representation())
		{
			switch(repr.first)
			{
				case FieldRepresentationType::Boolean:
				{
					HWND checkbox = std::get<HWND>(windows[i++]);
					auto state = SendMessageA(checkbox, BM_GETCHECK, 0, 0);
					bool checked = (state == BST_CHECKED);

					memcpy(newStruct.get() + j, &checked, sizeof(bool));
					j += sizeof(bool);
					break;
				}
				case FieldRepresentationType::Integer:
				{
					switch(structSize / field->Representation().size())
					{
						case sizeof(int8_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int8_t value = (int8_t)std::stoi(text);
							memcpy(newStruct.get() + j, &value, sizeof(int8_t));
							j += sizeof(int8_t);
							break;
						}
						case sizeof(int16_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int16_t value = (int16_t)std::stoi(text);
							memcpy(newStruct.get() + j, &value, sizeof(int16_t));
							j += sizeof(int16_t);
							break;
						}
						case sizeof(int32_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int32_t value = std::stol(text);
							memcpy(newStruct.get() + j, &value, sizeof(int32_t));
							j += sizeof(int32_t);
							break;
						}
						case sizeof(int64_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int64_t value = std::stoll(text);
							memcpy(newStruct.get() + j, &value, sizeof(int64_t));
							j += sizeof(int64_t);
							break;
						}
						default:
							throw std::logic_error("Unknown signed type");
					}
					break;
				}
				case FieldRepresentationType::Unsigned:
				{
					switch(structSize / field->Representation().size())
					{
						case sizeof(uint8_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							uint8_t value = (uint8_t)std::stoul(text);
							memcpy(newStruct.get() + j, &value, sizeof(uint8_t));
							j += sizeof(uint8_t);
							break;
						}
						case sizeof(uint16_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							uint16_t value = (uint16_t)std::stoul(text);
							memcpy(newStruct.get() + j, &value, sizeof(uint16_t));
							j += sizeof(uint16_t);
							break;
						}
						case sizeof(uint32_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							uint32_t value = std::stoul(text);
							memcpy(newStruct.get() + j, &value, sizeof(uint32_t));
							j += sizeof(uint32_t);
							break;
						}
						case sizeof(uint64_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							uint64_t value = std::stoull(text);
							memcpy(newStruct.get() + j, &value, sizeof(uint64_t));
							j += sizeof(uint64_t);
							break;
						}
						default:
							throw std::logic_error("Unknown unsigned type");
					}
					break;
				}
				case FieldRepresentationType::Float:
				{
					switch(structSize / field->Representation().size())
					{
						case sizeof(float) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							float value = std::stof(text);
							memcpy(newStruct.get() + j, &value, sizeof(float));
							j += sizeof(float);
							break;
						}
						case sizeof(double):
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							double value = std::stold(text);
							memcpy(newStruct.get() + j, &value, sizeof(double));
							j += sizeof(double);
							break;
						}
						default:
							throw std::logic_error("Unknown floating point type");
					}
					break;
				}
				case FieldRepresentationType::Quaternion:
				{
					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					float x = std::stof(text);
					
					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					float y = std::stof(text);

					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					float z = std::stof(text);

					Engine3DRadSpace::Math::Quaternion q = Engine3DRadSpace::Math::Quaternion::FromYawPitchRoll(y, x, z); // y = yaw, x = pitch, z = roll (?)

					memcpy(newStruct.get() + j, &q, sizeof(Engine3DRadSpace::Math::Quaternion));
					j += sizeof(Engine3DRadSpace::Math::Quaternion);
					break;
				}
				case FieldRepresentationType::String:
				{
					HWND textbox = std::get<HWND>(windows[i++]);
					int len = GetWindowTextLengthA(textbox);

					char* string = new char[len+1](0);

					GetWindowTextA(textbox, string, len);

					std::string *r = new std::string(string); //manually allocate a string.
					// "move" the string to an other location in the memory. the string object will be destroyed at the same time with the object that's being modified.
					memcpy(newStruct.get() + j, r, sizeof(std::string));
					j += sizeof(std::string);
					break;
				}
				case FieldRepresentationType::Image:
				{
					Engine3DRadSpace::Graphics::Texture2D *texture = nullptr;
					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					try
					{
						texture = new Engine3DRadSpace::Graphics::Texture2D(graphicsDevice, text);
					}
					catch(Engine3DRadSpace::Logging::ResourceLoadingError& loadingError)
					{
						std::string errMsg = loadingError.What();
						MessageBoxA(window, errMsg.c_str(), "Error creating texture!", MB_ICONERROR | MB_OK);

						if(texture != nullptr) delete texture;
						return false;
					}

					memcpy(newStruct.get(), texture, sizeof(Engine3DRadSpace::Graphics::Texture2D));
					j += sizeof(Engine3DRadSpace::Graphics::Texture2D);
					break;
				}
				case FieldRepresentationType::Model:
				{
					Engine3DRadSpace::Graphics::Model3D *model = nullptr;
					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					try
					{
						model = new Engine3DRadSpace::Graphics::Model3D(graphicsDevice, text);
					}
					catch(Engine3DRadSpace::Logging::ResourceLoadingError &e)
					{
						std::string msg = e.What();
						MessageBoxA(window, msg.c_str(), "Error creating model!", MB_ICONERROR | MB_OK);
						if(model != nullptr) delete model;
						return false;
					}

					memcpy(newStruct.get(), model, sizeof(Engine3DRadSpace::Graphics::Model3D));
					j += sizeof(Engine3DRadSpace::Graphics::Model3D);
					break;
				}
				case FieldRepresentationType::Key:
				{
					HWND hotkey = std::get<HWND>(windows[i++]);
					int r = SendMessageA(hotkey, HKM_GETHOTKEY, 0, 0);
					Input::Key k = static_cast<Input::Key>(LOBYTE(LOWORD(r)));
					if(k == Input::Key::None)
					{
						int alt_k = HIBYTE(LOWORD(r));
						if(alt_k == HOTKEYF_ALT) k = Input::Key::Alt;
						if(alt_k == HOTKEYF_SHIFT) k = Input::Key::Shift;
					}

					memcpy(newStruct.get(), &k, sizeof(Input::Key));
					j += sizeof(Input::Key);
					break;
				}
				case FieldRepresentationType::Enum:
				{
					break;
				}
				case FieldRepresentationType::Color:
				{
					GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
					uint8_t alpha = (uint8_t)std::stoi(text);

					ColorBox *cb = static_cast<ColorBox *>(std::get<IControl *>(windows[i++]));
					Engine3DRadSpace::Color color = cb->GetColor();
					color.A = ((float)alpha) / 255.0f;

					memcpy(newStruct.get(), &color, sizeof(Engine3DRadSpace::Color));
					j += sizeof(Engine3DRadSpace::Color);
					break;
				}
				case FieldRepresentationType::Custom:
				{
					break;
				}
			}
		}

		field->Set(object, newStruct.get());
	}
	return true;
}

Engine3DRadSpace::IObject* EditObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(this);
	if (r == IDOK) return this->object;
	return nullptr;
}

EditObjectDialog::~EditObjectDialog()
{
	for (HBITMAP bitmap : images)
	{
		DeleteObject(bitmap);
	}
}