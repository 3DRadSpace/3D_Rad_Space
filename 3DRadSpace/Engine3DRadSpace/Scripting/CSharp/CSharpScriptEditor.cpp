#include "CSharpScriptEditor.hpp"
#include "../../Logging/Warning.hpp"
#include <scintilla/Scintilla.h>
#include <scintilla/ILexer.h>
#include <lexilla/SciLexer.h>
#include <lexilla/Lexilla.h>
#include <string>

using namespace Engine3DRadSpace::Scripting::CSharp;

bool CSharpScriptEditor::_wasScintillaModuleLoaded = false;
bool CSharpScriptEditor::_wasLexillaModuleLoaded = false;
Lexilla::CreateLexerFn CSharpScriptEditor::_createLexer = nullptr;



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
	case WM_NOTIFY:
	{
		LPNMHDR pnmhdr = reinterpret_cast<LPNMHDR>(lParam);

		// Check if the notification is from the Scintilla control
		HWND scintilla = GetDlgItem(hwndDlg, IDC_CUSTOM1);
		if (pnmhdr->hwndFrom == scintilla && editor != nullptr)
		{
			if (pnmhdr->code == SCN_CHARADDED)
			{
				SCNotification* scn = reinterpret_cast<SCNotification*>(pnmhdr);
				editor->handleCharAdded(scintilla, scn->ch);
			}
			else if (pnmhdr->code == SCN_MODIFIED)
			{
				SCNotification* scn = reinterpret_cast<SCNotification*>(pnmhdr);
				// Only update line number margin if the text was actually modified
				// Check for SC_MOD_INSERTTEXT or SC_MOD_DELETETEXT flags
				if (scn->modificationType & (SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT))
				{
					editor->handleTextChanged(scintilla);
				}
			}
		}
		break;
	}
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
		case IDC_BUTTON1:
		{
			if (editor->_script->ScriptPath.empty())
			{
				editor->_script->ScriptPath = editor->saveFileDialog().string();
				editor->save(editor->_script->ScriptPath);
			}
			if (editor->_script->Class.empty())
			{
				HWND classNameTextbox = GetDlgItem(editor->_window, IDC_EDIT2);
				int lenClass = GetWindowTextLengthA(classNameTextbox);
				std::unique_ptr<char[]> classBuffer = std::make_unique<char[]>(lenClass + 1);
				GetWindowTextA(classNameTextbox, classBuffer.get(), lenClass + 1);
				editor->_script->Class = classBuffer.get();

				if (editor->_script->Class.empty())
				{
					MessageBoxA(hwndDlg, "Please specify a class name before compiling.", "Compilation Error", MB_OK | MB_ICONWARNING);
					break;
				}
			}
			try
			{
				auto startTime = std::chrono::high_resolution_clock::now();

				if (!editor->_script->Compile())
				{
					MessageBoxA(hwndDlg, "Script failed to compile. Check the log for details.", "Compilation Result", MB_OK | MB_ICONERROR);
				}

				auto endTime = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

				std::string message = "Script compiled successfully in " + std::to_string(duration) + " ms.";

				MessageBoxA(hwndDlg, message.c_str(), "Compilation Result", MB_OK | MB_ICONINFORMATION);
			}
			catch (const std::exception& e)
			{
				Engine3DRadSpace::Logging::PrintWarning(std::string("Exception caught: ") + e.what());
			}
			break;
		}
		case IDC_BUTTON2:
			editor->openFile();
			break;
		case IDC_BUTTON3:
			editor->_script->ScriptPath = editor->saveFileDialog().string();
			editor->save(editor->_script->ScriptPath);
			break;
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
	_wasAllocated(false),
	_maxLineNumberCharLength(0),
	_codeControl(nullptr),
	_lexer(nullptr)
{
	if (!_wasScintillaModuleLoaded)
	{
		auto scintillaModule = LoadLibraryA("Scintilla.dll");
		if (scintillaModule == NULL)
		{
			Logging::PrintWarning("Scintilla wasn't loaded, using an EDIT control.");
			_createNewObject(object);
			return;
		}

		_wasScintillaModuleLoaded = true;
	}

	if (!_wasLexillaModuleLoaded)
	{
		auto lexillaModule = LoadLibraryA("Lexilla.dll");
		if (lexillaModule == nullptr)
		{
			Logging::PrintWarning("Lexilla wasn't loaded, syntax highlighting will not work.");
		}
		else
		{
			_createLexer = reinterpret_cast<Lexilla::CreateLexerFn>(GetProcAddress(lexillaModule, "CreateLexer"));
			if (_createLexer == nullptr)
			{
				Logging::PrintWarning("Lexilla CreateLexer function not found, syntax highlighting will not work.");
			}
		}

		_wasLexillaModuleLoaded = true;
	}

	// Create a new lexer instance for this editor window
	if (_createLexer != nullptr)
	{
		_lexer = _createLexer("cpp");
		if (_lexer == nullptr)
		{
			Logging::PrintWarning("Failed to create C++ lexer, syntax highlighting will not work.");
		}
	}

	_createNewObject(object);
}

void CSharpScriptEditor::_createNewObject(CSharpScript* object)
{
	if (object == nullptr)
	{
		_script = new CSharpScript();
		_wasAllocated = true;
	}
}

CSharpScriptEditor::~CSharpScriptEditor()
{
	if (_lexer != nullptr)
	{
		_lexer->Release();
		_lexer = nullptr;
	}
}

void CSharpScriptEditor::initForms()
{
	HWND nameTextbox = GetDlgItem(_window, IDC_EDIT1);
	SetWindowTextA(nameTextbox, _script->Name.c_str());

	HWND enabledCheckbox = GetDlgItem(_window, IDC_CHECK1);
	SendMessageA(enabledCheckbox, BM_SETCHECK, _script->Enabled ? BST_CHECKED : BST_UNCHECKED, 0);

	HWND classNameTextbox = GetDlgItem(_window, IDC_EDIT2);
	SetWindowTextA(classNameTextbox, _script->Class.c_str());

	_codeControl = GetDlgItem(_window, IDC_CUSTOM1);
	if (!_codeControl || !_wasScintillaModuleLoaded)
	{
		_codeControl = CreateWindowExA(0, "Edit", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN, 10, 100, 400, 200, _window, nullptr, _hInstance, nullptr);

		return;
	}

	if (_lexer)
	{
		SendMessageA(_codeControl, SCI_SETILEXER, 0, reinterpret_cast<LPARAM>(_lexer));
		// Scintilla takes ownership after SCI_SETILEXER and will call Release() itself.
		// Clear the pointer so we don't double-release the object.
		_lexer = nullptr;
	}

	// Reset and clear styles
	SendMessageA(_codeControl, SCI_STYLERESETDEFAULT, 0, 0);
	SendMessageA(_codeControl, SCI_STYLECLEARALL, 0, 0);

	// Set default font and size
	SendMessageA(_codeControl, SCI_STYLESETFONT, SCE_C_DEFAULT, reinterpret_cast<LPARAM>("Consolas"));
	SendMessageA(_codeControl, SCI_STYLESETSIZE, SCE_C_DEFAULT, 10);

	// Configure the CPP (C#) lexer styles
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_DEFAULT, RGB(192, 192, 192)); // Silver
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_COMMENT, RGB(0, 128, 0)); // Green
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_COMMENTLINE, RGB(0, 128, 0)); // Green
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_COMMENTDOC, RGB(128, 128, 128)); // Gray
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_NUMBER, RGB(128, 128, 0)); // Olive
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_WORD, RGB(0, 0, 255)); // Blue
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_WORD2, RGB(0, 0, 255)); // Blue
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_STRING, RGB(163, 21, 21)); // Red
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_CHARACTER, RGB(163, 21, 21)); // Red
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_VERBATIM, RGB(163, 21, 21)); // Red
	SendMessageA(_codeControl, SCI_STYLESETBACK, SCE_C_STRINGEOL, RGB(255, 192, 203)); // Pink
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_OPERATOR, RGB(128, 0, 128)); // Purple
	SendMessageA(_codeControl, SCI_STYLESETFORE, SCE_C_PREPROCESSOR, RGB(128, 0, 0)); // Maroon

	SendMessageA(_codeControl, SCI_SETKEYWORDS, 0, reinterpret_cast<WPARAM>(
		"abstract as base break case catch checked continue default delegate do else event explicit extern false finally "
		"fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override "
		"params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof "
		" unchecked unsafe using virtual while"
		));

	SendMessageA(_codeControl, SCI_SETKEYWORDS, 1, reinterpret_cast<WPARAM>(
		"bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort void"
		));

	SendMessageA(_codeControl, SCI_SETKEYWORDS, 2, reinterpret_cast<WPARAM>(
		"add alias ascending async await by descending dynamic equals from get global group into join let nameof on orderby partial "
		"remove select set value var when where yield"
		));

	if (std::filesystem::exists(_script->ScriptPath))
	{
		_loadCodeFromFile(_script->ScriptPath);
	}
	else
	{
		_loadCodeFromFile("Scripts\\Empty.cs");
	}
}

void CSharpScriptEditor::handleCharAdded(HWND scintilla, int ch)
{
	// Get the current position
	sptr_t currentPos = SendMessageA(scintilla, SCI_GETCURRENTPOS, 0, 0);

	// Find the word start position
	sptr_t wordStartPos = SendMessageA(scintilla, SCI_WORDSTARTPOSITION, currentPos, 1);

	// Calculate the length of entered characters
	sptr_t lenEntered = currentPos - wordStartPos;

	if (lenEntered > 0)
	{
		// Check if autocomplete is already active
		sptr_t autoCActive = SendMessageA(scintilla, SCI_AUTOCACTIVE, 0, 0);
		if (!autoCActive)
		{
			// Display the autocompletion list
			const char* keywordList = 
				"abstract as base break case catch checked continue default delegate do else event explicit extern false finally "
				"fixed for foreach goto if implicit in interface internal is lock namespace new null object operator out override "
				"params private protected public readonly ref return sealed sizeof stackalloc switch this throw true try typeof "
				"unchecked unsafe using virtual while "
				"bool byte char class const decimal double enum float int long sbyte short static string struct uint ulong ushort void "
				"add alias ascending async await by descending dynamic equals from get global group into join let nameof on orderby partial "
				"remove select set value var when where yield";

			SendMessageA(scintilla, SCI_AUTOCSHOW, lenEntered, reinterpret_cast<LPARAM>(keywordList));
		}
	}
}

void CSharpScriptEditor::handleTextChanged(HWND scintilla)
{
	// Get the number of lines
	sptr_t lineCount = SendMessageA(scintilla, SCI_GETLINECOUNT, 0, 0);

	// Convert line count to string to get its character length
	const int maxLineNumberCharLength = static_cast<int>(std::to_string(lineCount).length());

	// If the character length hasn't changed, return early
	if (maxLineNumberCharLength == _maxLineNumberCharLength)
		return;

	// Calculate the width required to display the line numbers
	// We use '9' characters as a measure since they're typically the widest digits
	const int padding = 2;
	std::string measureStr(maxLineNumberCharLength + 1, '9');

	// Use SCI_TEXTWIDTH to get the pixel width of the line number string
	// STYLE_LINENUMBER is the style used for line numbers
	sptr_t width = SendMessageA(scintilla, SCI_TEXTWIDTH, STYLE_LINENUMBER, reinterpret_cast<LPARAM>(measureStr.c_str()));

	// Set the margin width (margin 0 is the line number margin)
	SendMessageA(scintilla, SCI_SETMARGINWIDTHN, 0, width + padding);

	// Update the stored line number character length
	_maxLineNumberCharLength = maxLineNumberCharLength;
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
		if (_script->ScriptPath.empty())
		{
			auto path = saveFileDialog().string();
			if (!path.empty())
			{
				_script->ScriptPath = path;
				save(path);
			}
			else return nullptr;
		}
		return _script;
	}
	return nullptr;
}

std::filesystem::path CSharpScriptEditor::saveFileDialog()
{
	OPENFILENAMEA ofn{};
	char fileName[MAX_PATH] = { 0 };	
	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;;
	ofn.hwndOwner = _window;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);

	if (GetSaveFileNameA(&ofn))
	{
		return std::filesystem::path(fileName);
	}
	else return {};
}

std::filesystem::path CSharpScriptEditor::openFileDialog()
{
	OPENFILENAMEA ofn{};
	char fileName[MAX_PATH] = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.hwndOwner = _window;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	if (GetOpenFileNameA(&ofn))
	{
		return std::filesystem::path(fileName);
	}
	else return {};
}

void CSharpScriptEditor::_loadCodeFromFile(const std::filesystem::path& path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string scriptText((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		SendMessageA(_codeControl, SCI_SETTEXT, 0, reinterpret_cast<LPARAM>(scriptText.c_str()));
	}
}

void CSharpScriptEditor::openFile()
{
	std::filesystem::path path = openFileDialog();
	if (!path.empty())
	{
		_script->ScriptPath = path.string();
		_loadCodeFromFile(_script->ScriptPath);
	}
}

void CSharpScriptEditor::save(const std::filesystem::path& path)
{
	std::ofstream file(path, std::ios::binary);
	if (file.is_open())
	{
		sptr_t length = SendMessageA(_codeControl, SCI_GETLENGTH, 0, 0);
		std::unique_ptr<char[]> buffer = std::make_unique<char[]>(length + 1);
		SendMessageA(_codeControl, SCI_GETTEXT, length + 1, reinterpret_cast<LPARAM>(buffer.get()));
		file.write(buffer.get(), length);
	}
}
