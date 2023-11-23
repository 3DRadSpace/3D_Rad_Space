#include "EditObjectDialog.hpp"
#include "..\Controls\NumericTextbox.hpp"
#include "..\Controls\ColorBox.hpp"
#include <Engine3DRadSpace/IObject.hpp>
#include <Engine3DRadSpace/Logging/ResourceLoadingError.hpp>
#include "EditorWindow.hpp"
#include "..\Controls\TextureControl.hpp"
#include "..\Controls\ModelControl.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics;
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
					{
						EndDialog(hwnd, IDOK);
						return 1;
					}
				}
				if(lParam == reinterpret_cast<LPARAM>(eod->cancelButton))
				{
					EndDialog(hwnd, IDCANCEL);
					return 1;
				}

				for(auto &c : eod->windows)
				{
					auto control = std::get_if<IControl *>(&c);
					if(control != nullptr)
					{
						(*control)->HandleClick(reinterpret_cast<HWND>(lParam));
					}
				}
				return 0;
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

EditObjectDialog::EditObjectDialog(HWND owner, HINSTANCE hInstance, ReflectedObject *data, ContentManager *content, IObject *obj) :
	Dialog(owner, hInstance, EditObjectDialog_DlgProc, data->Name + " object"),
	objRefl(data),
	object(obj),
	helpButton(nullptr),
	okButton(nullptr),
	cancelButton(nullptr),
	_content(content)
{
	assert(data != nullptr);
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
			auto createLabel = [&](const std::string &text, int &size_x) -> HWND
			{
				SIZE size;
				GetTextExtentPointA(hdc, text.c_str(), int(text.length()), &size);
				
				size_x = size.cx;
				return CreateWindowExA(
					0,
					"Static",
					text.c_str(),
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
			auto createTextbox = [&](const char* value) -> HWND
			{
				return CreateWindowExA(
					0,
					"Edit",
					value,
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
			auto createNumericTextbox = [&](const char* defValue) -> IControl*
			{
				return new NumericTextbox(window, hInstance, px, y, 75, textboxHeight, defValue);
			};

			//Value of the field, either from the object that's being edited, or a default value.
			const void* valuePtr = object != nullptr ? field->Get(object) : field->DefaultValue();

			switch (repr.first)
			{
			case FieldRepresentationType::Boolean:
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
				bool value = *reinterpret_cast<const bool*>(static_cast<const char*>(valuePtr) + fOffset);
				SendMessageA(checkBox, BM_SETCHECK, value ? BST_CHECKED : BST_UNCHECKED, 0);

				//update coordinates
				setMax(inc_y, 30);
				px += fieldNameSize.cx + checkBoxLen + 5;
				break;
			}
			case FieldRepresentationType::Integer:
			{
				int sx;

				createLabel(fieldName, sx);
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
			case FieldRepresentationType::Unsigned:
			{
				int sx;
				createLabel(fieldName, sx);
				px += sx + 5;

				//Get unsigned value.
				uint64_t value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(uint8_t) :
						value = *reinterpret_cast<const uint8_t *>(static_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint8_t);
						break;
					case sizeof(uint16_t) :
						value = *reinterpret_cast<const uint16_t *>(static_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint16_t);
						break;
					case sizeof(uint32_t) :
						value = *reinterpret_cast<const uint32_t *>(static_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(uint32_t);
						break;
					case sizeof(uint64_t) :
						value = *reinterpret_cast<const uint64_t *>(static_cast<const char *>(valuePtr) + fOffset);
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
			case FieldRepresentationType::Float:
			{
				int sx;
				createLabel(fieldName, sx);
				px += sx + 5;

				double value = 0;
				switch (field->TypeSize() / field->Representation().size())
				{
					case sizeof(float) :
						value = *reinterpret_cast<const float *>(static_cast<const char *>(valuePtr) + fOffset);
						fOffset += sizeof(float);
						break;
					case sizeof(double) :
						value = *reinterpret_cast<const double *>(static_cast<const char *>(valuePtr) + fOffset);
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
			case FieldRepresentationType::Quaternion:
			{
				//read value
				auto q = *reinterpret_cast<const Math::Quaternion *>(static_cast<const char *>(valuePtr) + fOffset);
				auto eulerAngles = q.ToYawPitchRoll();

				auto pitch = std::to_string(Math::ToDegrees(eulerAngles.X));
				auto yaw = std::to_string(Math::ToDegrees(eulerAngles.Y));
				auto roll = std::to_string(Math::ToDegrees(eulerAngles.Z));

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
			case FieldRepresentationType::String:
			{
				int sx;
				createLabel(fieldName, sx);
				px += sx + 5;

				const std::string value = *static_cast<const std::string*>(valuePtr);
				windows.push_back(createTextbox(value.c_str()));

				px += sx + 5;
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case FieldRepresentationType::Image:
			{
				auto value = *static_cast<const AssetReference<Texture2D>*>(valuePtr);
				
				TextureControl *ctrl = new TextureControl(window, hInstance, _content, value, fieldName, x, y);
				windows.push_back(ctrl);

				setMax(inc_y, 205 + textboxHeight);
				px = ctrl->AccX() > 205 ? ctrl->AccX() : 205;
				break;
			}
			case FieldRepresentationType::Model:
			{
				auto value = *static_cast<const AssetReference<Model3D>*>(valuePtr);

				ModelControl* ctrl = new ModelControl(window, hInstance, _content, value, fieldName, x, y);
				windows.push_back(ctrl);

				setMax(inc_y, 205 + textboxHeight);
				px = ctrl->AccX() > 205 ? ctrl->AccX() : 205;
				break;
			}
			case FieldRepresentationType::Key:
			{
				int sx;
				createLabel(fieldName, sx);
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

				auto key = static_cast<const Input::Key*>(valuePtr);
				SendMessageA(hotkey, HKM_SETHOTKEY, static_cast<WPARAM>(LOBYTE(key)), 0);

				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case FieldRepresentationType::Enum:
			{
				int sx;
				createLabel(fieldName, sx);
				px += sx + 5;
				//TODO: Create a combo box with all enum types

				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case FieldRepresentationType::Color:
			{
				int sx;
				Color color = *static_cast<const Color*>(valuePtr);

				createLabel("Alpha", sx);
				px += sx;

				std::string alphaStr = std::to_string(color.A);
				windows.push_back(createTextbox(alphaStr.c_str()));
				px += 80;

				windows.push_back(new ColorBox(window, hInstance,px,y,25,25, color));
				px += 30;
				setMax(inc_y, textboxHeight + 5);
				break;
			}
			case FieldRepresentationType::Custom:
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
		auto newStruct = std::make_unique<uint8_t[]>(structSize);
		int j = 0;
		char text[256] = {0};

		auto graphicsDevice = object != nullptr ? object->GetGraphicsDeviceHandle() : gEditorWindow->GetGraphicsDevice();
		
		if(object == nullptr)
			object = objRefl->CreateBlankObject();

		for(auto &repr : field->Representation())
		{
			switch(repr.first)
			{
				case FieldRepresentationType::Boolean:
				{
					HWND checkbox = std::get<HWND>(windows[i++]);
					auto state = SendMessageA(checkbox, BM_GETCHECK, 0, 0);
					bool checked = (state == BST_CHECKED);

					memcpy_s(newStruct.get() + j, sizeof(bool), &checked, sizeof(bool));
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
							memcpy_s(newStruct.get() + j, sizeof(int8_t), &value, sizeof(int8_t));
							j += sizeof(int8_t);
							break;
						}
						case sizeof(int16_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int16_t value = (int16_t)std::stoi(text);
							memcpy_s(newStruct.get() + j,sizeof(int16_t), &value, sizeof(int16_t));
							j += sizeof(int16_t);
							break;
						}
						case sizeof(int32_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int32_t value = std::stol(text);
							memcpy_s(newStruct.get() + j,sizeof(int32_t), &value, sizeof(int32_t));
							j += sizeof(int32_t);
							break;
						}
						case sizeof(int64_t) :
						{
							GetWindowTextA(std::get<HWND>(windows[i++]), text, 255);
							int64_t value = std::stoll(text);
							memcpy_s(newStruct.get() + j, sizeof(int64_t), & value, sizeof(int64_t));
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
					auto numericTextbox = static_cast<NumericTextbox *>(std::get<IControl *>(windows[i++]));
					GetWindowTextA(*numericTextbox, text, 255);

					switch(structSize / field->Representation().size())
					{
						case sizeof(uint8_t) :
						{
							uint8_t value = (uint8_t)std::stoul(text);
							memcpy_s(newStruct.get() + j, sizeof(uint8_t), &value, sizeof(uint8_t));
							j += sizeof(uint8_t);
							break;
						}
						case sizeof(uint16_t) :
						{
							uint16_t value = (uint16_t)std::stoul(text);
							memcpy_s(newStruct.get() + j, sizeof(uint16_t),  &value, sizeof(uint16_t));
							j += sizeof(uint16_t);
							break;
						}
						case sizeof(uint32_t) :
						{
							uint32_t value = std::stoul(text);
							memcpy_s(newStruct.get() + j, sizeof(uint32_t), &value, sizeof(uint32_t));
							j += sizeof(uint32_t);
							break;
						}
						case sizeof(uint64_t) :
						{
							uint64_t value = std::stoull(text);
							memcpy_s(newStruct.get() + j, sizeof(uint64_t), &value, sizeof(uint64_t));
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
					auto numericTextbox = static_cast<NumericTextbox *>(std::get<IControl *>(windows[i++]));
					GetWindowTextA(*numericTextbox, text, 255);

					switch(structSize / field->Representation().size())
					{
						case sizeof(float) :
						{
							float value = std::stof(text);
							memcpy_s(newStruct.get() + j, sizeof(float), & value, sizeof(float));
							j += sizeof(float);
							break;
						}
						case sizeof(double):
						{
							double value = std::stod(text);
							memcpy_s(newStruct.get() + j, sizeof(float), &value, sizeof(double));
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
					GetWindowTextA(
						*static_cast<NumericTextbox*>(std::get<IControl*>(windows[i++])),
						text,
						255
					);
					float x = Math::ToRadians(std::stof(text));
					
					GetWindowTextA(
						*static_cast<NumericTextbox *>(std::get<IControl *>(windows[i++])),
						text,
						255
					);
					float y = Math::ToRadians(std::stof(text));

					GetWindowTextA(
						*static_cast<NumericTextbox *>(std::get<IControl *>(windows[i++])),
						text,
						255
					);
					float z = Math::ToRadians(std::stof(text));

					Math::Quaternion q = Math::Quaternion::FromYawPitchRoll(x, y, z); // y = yaw, x = pitch, z = roll (?)

					memcpy_s(newStruct.get() + j, sizeof(Math::Quaternion), &q, sizeof(Math::Quaternion));
					j += sizeof(Math::Quaternion);
					break;
				}
				case FieldRepresentationType::String:
				{
					HWND textbox = std::get<HWND>(windows[i++]);
					int len = GetWindowTextLengthA(textbox);

					char* string = new char[len+1](0);
					GetWindowTextA(textbox, string, len+1);

					std::string *dest = reinterpret_cast<std::string*>(newStruct.get() + j);

					new (dest) std::string(string);
					j += sizeof(std::string);

					break;
				}
				case FieldRepresentationType::Image:
				{
					auto textureControl = static_cast<TextureControl *>(std::get<IControl *>(windows[i++]));
					
					memcpy_s(newStruct.get() + j, sizeof(RefTexture2D), &textureControl->TextureReference, sizeof(RefTexture2D));
					j += sizeof(RefTexture2D);
					break;
				}
				case FieldRepresentationType::Model:
				{
					auto modelControl = static_cast<ModelControl*>(std::get<IControl*>(windows[i++]));

					memcpy_s(newStruct.get() + j, sizeof(RefModel3D), &modelControl->ModelReference, sizeof(RefModel3D));
					j += sizeof(RefModel3D);
					break;
				}
				case FieldRepresentationType::Key:
				{
					HWND hotkey = std::get<HWND>(windows[i++]);
					int r = (int)SendMessageA(hotkey, HKM_GETHOTKEY, 0, 0);
					Input::Key k = static_cast<Input::Key>(LOBYTE(LOWORD(r)));
					if(k == Input::Key::None)
					{
						int alt_k = HIBYTE(LOWORD(r));
						if(alt_k == HOTKEYF_ALT) k = Input::Key::Alt;
						if(alt_k == HOTKEYF_SHIFT) k = Input::Key::Shift;
					}

					memcpy_s(newStruct.get(), sizeof(Input::Key), &k, sizeof(Input::Key));
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
					Color color = cb->GetColor();
					color.A = ((float)alpha);

					memcpy_s(newStruct.get(), sizeof(Color), &color, sizeof(Color));
					j += sizeof(Color);
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

IObject* EditObjectDialog::ShowDialog()
{
	INT_PTR r = Dialog::ShowDialog(this);
	if (r == IDOK) return this->object;
	return nullptr;
}

EditObjectDialog::~EditObjectDialog()
{
	for(auto &c : windows)
	{
		auto control = std::get_if<IControl *>(&c);
		if(control != nullptr) delete *control;
	}
}