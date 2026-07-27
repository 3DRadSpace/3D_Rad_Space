#include "NETCoreHost.hpp"
#include "../../Logging/Message.hpp"
#include "../../Logging/Warning.hpp"
#include "../../Native/LibraryLoader.hpp"
#include "../../Plugins/EditorPlugin.hpp"
#include "../../Plugins/CustomObject.hpp"

using namespace Engine3DRadSpace;

hostfxr_initialize_for_runtime_config_fn init_fptr;
hostfxr_get_runtime_delegate_fn get_delegate_fptr;
hostfxr_close_fn close_fptr;

extern string_t fxrPath;

bool load_hostfxr()
{
	if(!std::filesystem::exists(csharpAssemblyPath))
	{
		Logging::PrintWarning("C# Assembly is not found. It should be located at \"<root>\\3DRadSpace_CSharp.dll\"");
		return false;
	}

	get_hostfxr_parameters params(sizeof(get_hostfxr_parameters), csharpAssemblyPath, nullptr);

	//1st call to get bufferSize
	size_t bufferSize = 0;
	get_hostfxr_path(nullptr, &bufferSize, &params);

	//Actual call
	std::unique_ptr<char_t[]> fxrPathBuffer = std::make_unique<char_t[]>(bufferSize);
	int rc = get_hostfxr_path(fxrPathBuffer.get(), &bufferSize, &params);
	if (rc != 0)
		return false;

	fxrPath = fxrPathBuffer.get();

	// Load hostfxr and get desired exports
	void* lib = Native::Load_Library(std::filesystem::path(fxrPath));
	init_fptr = Native::GetFunctionFromLibrary<hostfxr_initialize_for_runtime_config_fn>(lib, "hostfxr_initialize_for_runtime_config");
	get_delegate_fptr = Native::GetFunctionFromLibrary<hostfxr_get_runtime_delegate_fn>(lib, "hostfxr_get_runtime_delegate");
	close_fptr = Native::GetFunctionFromLibrary<hostfxr_close_fn>(lib, "hostfxr_close");

	return (init_fptr && get_delegate_fptr && close_fptr);
}

load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path)
{
	// Load .NET Core
	void* load_assembly_and_get_function_pointer = nullptr;
	hostfxr_handle cxt = nullptr;
	int rc = init_fptr(config_path, nullptr, &cxt);
	if (rc != 0 || cxt == nullptr)
	{
		Logging::PrintWarning(std::format("get_dotnet_load_assembly Init failed: rc {:x} cxt: {:x} ", rc, reinterpret_cast<intptr_t>(cxt)));
		close_fptr(cxt);
		return nullptr;
	}

	// Get the load assembly function pointer
	rc = get_delegate_fptr(
		cxt,
		hdt_load_assembly_and_get_function_pointer,
		&load_assembly_and_get_function_pointer);
	if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
		Logging::PrintWarning(std::format("Get delegate failed {:x} ", rc));

	close_fptr(cxt);
	return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
}

load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer;