#include "EditorPlugin.hpp"
#include "../Native/LibraryLoader.hpp"
#include "../Objects/Impl/Objects.hpp"
#include "../FFI/Core/RawSpan.h"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Plugins;
using namespace Engine3DRadSpace::Native;

std::expected<std::pair<PluginInfo, void*>, PluginLoadingError> Engine3DRadSpace::Plugins::LoadPlugin(const std::filesystem::path& pluginPath)
{
	auto plugin = Load_Library(pluginPath);
	if(!plugin) return std::unexpected(PluginLoadingError::UnableToLoadPluginLibrary);

	auto initialize_fn = GetFunctionFromLibrary<PluginMain>(plugin, "PluginMain");
	if(!initialize_fn) return std::unexpected(PluginLoadingError::NotA3DRadSpacePlugin);

	auto get_info = GetFunctionFromLibrary<LoadPluginInfo>(plugin, "LoadPluginInfo");
	if(!get_info) return std::unexpected(PluginLoadingError::NotA3DRadSpacePlugin);

	if(!initialize_fn()) return std::unexpected(PluginLoadingError::InitializationFunctionFailure);

	typedef E3DRSP_RawSpan (*LoadCustomObjectsFn)();
	auto load_objects_fn = GetFunctionFromLibrary<LoadCustomObjectsFn>(plugin, "LoadCustomObjects");
	if(load_objects_fn)
	{
		auto span = load_objects_fn();
		auto begin = static_cast<Engine3DRadSpace::Reflection::ReflectedObject*>(span.Ptr);
		for(size_t i = 0; i < span.Size; ++i)
		{
			auto* obj = &begin[i];
			bool duplicate = std::any_of(
				e3drsp_internal_objects_list.begin(),
				e3drsp_internal_objects_list.end(),
				[obj](Engine3DRadSpace::Reflection::ReflectedObject* existing) { return existing->ObjectUUID == obj->ObjectUUID; }
			);
			if(!duplicate)
				e3drsp_internal_objects_list.push_back(obj);
		}
	}

	return std::make_pair<PluginInfo, void*>(get_info(), static_cast<void*>(plugin));
}
