#include "ObjectEditorWindow.hpp"

ObjectEditorWindow::ObjectEditorWindow(
	std::function<Engine3DRadSpace::IObject* ()> f, 
	Engine3DRadSpace::Reflection::Reflect& refl,
	Engine3DRadSpace::Point WndSize, 
	const char* helpUrl, 
	const char* helpFile,
	const char* objName, 
	FieldGroup* groups, 
	size_t numGroups) 
	:
	CreateEmptyObject(f),
	Reflection(refl),
	WindowSize(WndSize),
	HelpURLAddress(helpUrl),
	OfflineHelpPath(helpFile),
	Name(objName),
	Groups(groups),
	NumGroups(numGroups)
{
}
