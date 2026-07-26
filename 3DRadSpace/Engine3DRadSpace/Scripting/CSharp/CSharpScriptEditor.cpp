#include "CSharpScriptEditor.hpp"
#include "../../Logging/Warning.hpp"

using namespace Engine3DRadSpace::Scripting::CSharp;

INT_PTR CALLBACK CSharpEditorDlgProc(
	HWND hwndDlg,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	CSharpScriptEditor* editor = nullptr;

	if (message == WM_INITDIALOG)
	{
		editor = reinterpret_cast<CSharpScriptEditor*>(lParam);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(editor));
		editor->_window = hwndDlg;
		editor->initForms();
		return TRUE;
	}

	editor = reinterpret_cast<CSharpScriptEditor*>(GetWindowLongPtr(hwndDlg, GWLP_USERDATA));

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND nameTextbox = GetDlgItem(editor->_window, IDC_EDIT1);
			int lenName = GetWindowTextLengthA(nameTextbox);
			std::unique_ptr<char[]> nameBuffer = std::make_unique<char[]>(lenName + 1);
			GetWindowTextA(nameTextbox, nameBuffer.get(), lenName + 1);
			editor->_script->Name = nameBuffer.get();

			HWND classNameTextbox = GetDlgItem(editor->_window, IDC_EDIT2);
			int lenClass = GetWindowTextLengthA(classNameTextbox);
			std::unique_ptr<char[]> classBuffer = std::make_unique<char[]>(lenClass + 1);
			GetWindowTextA(classNameTextbox, classBuffer.get(), lenClass + 1);
			editor->_script->Class = classBuffer.get();

			HWND enabledCheckbox = GetDlgItem(editor->_window, IDC_CHECK1);
			editor->_script->Enabled = (SendMessageA(enabledCheckbox, BM_GETCHECK, 0, 0) == BST_CHECKED);

			EndDialog(hwndDlg, IDOK);
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hwndDlg, IDCANCEL);
			if (editor->_script != nullptr && editor->_wasAllocated)
			{
				delete editor->_script;
				editor->_script = nullptr;
			}
			return TRUE;
		case IDC_BUTTON4:
			ShellExecuteA(nullptr, "open", "https://3dradspace.github.io/docs/scripting/csharp.html", nullptr, nullptr, SW_SHOWNORMAL);
			break;
		}
		break;
	}
	return FALSE;
}

void* CreateCSharpEditorWindow(HWND dlgOwner, HINSTANCE hInstance, void* reflectionData, void* contentManager, void* object)
{
	auto refl = static_cast<Engine3DRadSpace::Reflection::ReflectedObject*>(reflectionData);
	auto content = static_cast<Engine3DRadSpace::Content::ContentManager*>(contentManager);
	auto obj = static_cast<Engine3DRadSpace::Scripting::CSharp::CSharpScript*>(object);

	HMODULE moduleHandle = hInstance;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		reinterpret_cast<LPCSTR>(&CreateCSharpEditorWindow),
		reinterpret_cast<HMODULE*>(&moduleHandle)
	);

	CSharpScriptEditor editor(dlgOwner, moduleHandle, obj);
	return static_cast<void*>(editor.ShowDialog());
}

CSharpScriptEditor::CSharpScriptEditor(
	HWND dlgOwner,
	HINSTANCE hInstance,
	CSharpScript* object
) : _window(nullptr),
	_hInstance(hInstance),
	_owner(dlgOwner),
	_script(object),
	_wasAllocated(false)
{
	static bool wasScintillaModuleLoaded = false;

	if (!wasScintillaModuleLoaded)
	{
		auto scintillaModule = LoadLibrary("Scintilla.dll");
		if (scintillaModule == NULL)
		{
			WNDCLASSA scintillaClass{};
			scintillaClass.lpszClassName = "Scintilla";
			scintillaClass.lpfnWndProc = DefWindowProcA;
			scintillaClass.hInstance = _hInstance;

			RegisterClassA(&scintillaClass);

			Logging::SetLastWarning("Scintilla wasn't loaded, using an EDIT control.");
		}

		wasScintillaModuleLoaded = true;
	}

	if (object == nullptr)
	{
		_script = new CSharpScript();
		_wasAllocated = true;
	}
}

void CSharpScriptEditor::initForms()
{
	//SetClassLongPtr(_window,          // window handle 
	//	GCLP_HICON,              // changes icon 
	//	(LONG_PTR)LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1))
	//);

	HWND nameTextbox = GetDlgItem(_window, IDC_EDIT1);
	SetWindowTextA(nameTextbox, _script->Name.c_str());

	HWND enabledCheckbox = GetDlgItem(_window, IDC_CHECK1);
	SendMessageA(enabledCheckbox, BM_SETCHECK, _script->Enabled ? BST_CHECKED : BST_UNCHECKED, 0);

	HWND classNameTextbox = GetDlgItem(_window, IDC_EDIT2);
	SetWindowTextA(classNameTextbox, _script->Class.c_str());
}

CSharpScript* CSharpScriptEditor::ShowDialog()
{
	INT_PTR dlg = DialogBoxParam(
		_hInstance,
		MAKEINTRESOURCE(ID_CSHARPDIALOG),
		_owner,
		CSharpEditorDlgProc,
		reinterpret_cast<LPARAM>(this)
	);
	if (dlg == IDOK)
	{
		return _script;
	}
	return nullptr;
}