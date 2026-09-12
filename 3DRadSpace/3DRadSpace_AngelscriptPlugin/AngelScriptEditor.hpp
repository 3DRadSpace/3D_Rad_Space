#pragma once
#include "AngelScriptObject.hpp"
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include "resource.h"
#include <Windows.h>

namespace Scintilla { class ILexer5; }
namespace Lexilla { using CreateLexerFn = Scintilla::ILexer5* (*)(const char* name); }

extern "C"
{
	__declspec(dllexport) void* CreateAngelScriptEditorWindow(HWND dlgOwner, HINSTANCE hInstance, void* reflectionData, void* contentManager, void* object);
}

INT_PTR CALLBACK AngelScriptEditorDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

namespace Engine3DRadSpace::Angelscript
{
	class AngelScriptEditor
	{
		HWND _window;
		HINSTANCE _hInstance;
		HWND _owner;
		AngelScriptObject* _script;
		bool _wasAllocated;
		static bool _wasScintillaModuleLoaded;
		static bool _wasLexillaModuleLoaded;
		static Lexilla::CreateLexerFn _createLexer;
		int _maxLineNumberCharLength;
		HWND _codeControl;
		Scintilla::ILexer5* _lexer;

		void initForms();
		void handleCharAdded(HWND scintilla, int ch);
		void handleTextChanged(HWND scintilla);

		void _loadCodeFromFile(const std::filesystem::path& path);
		void load(const std::filesystem::path& path);
		void save(const std::filesystem::path& path);

		std::filesystem::path saveFileDialog();
		std::filesystem::path openFileDialog();
		void openFile();

		void _createNewObject(AngelScriptObject* object);
	public:
		AngelScriptEditor(
			HWND dlgOwner, 
			HINSTANCE hInstance,
			AngelScriptObject* object
		);

		AngelScriptEditor(const AngelScriptEditor&) = delete;
		AngelScriptEditor& operator=(const AngelScriptEditor&) = delete;

		AngelScriptEditor(AngelScriptEditor&&) = delete;
		AngelScriptEditor& operator=(AngelScriptEditor&&) = delete;

		AngelScriptObject* ShowDialog();

		~AngelScriptEditor();

		friend INT_PTR CALLBACK ::AngelScriptEditorDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
	};
}