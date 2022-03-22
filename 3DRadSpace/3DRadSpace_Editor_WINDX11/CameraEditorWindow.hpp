#pragma once
#include "IObjectEditorWindow.hpp"

class CameraEditorWindow : public IObjectEditorWindow
{
	static __stdstring _gFieldNames[];
	static __stdstring _gFieldValues[];
public:
	virtual Engine3DRadSpace::IObject* CreateObject(std::vector<__stdstring> &fieldValues) override;
	virtual const __rawstring GetHelpURL() override;
	virtual const char* GetObjectName() override;
	virtual __stdstring* GetFieldNames() override;
	virtual size_t GetFieldNamesCount() override;
	virtual __stdstring* GetFieldValues() override;
	virtual size_t GetFieldValuesCount() override;
	virtual std::vector<EditableFieldType> GetFieldFormTypes() override;
};

