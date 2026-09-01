#include "PluginManager.hpp"
#include "../Logging/Message.hpp"
#include "../Logging/Warning.hpp"
#include "../Native/LibraryLoader.hpp"
#include "CustomObject.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Plugins;

PluginManager::PluginManager(IGame* owner)
	: IService(owner)
{
	std::filesystem::create_directories("Plugins");
	auto dirIterator = std::filesystem::directory_iterator("Plugins");

	//Count .dll files in "./Plugins"
	unsigned numPlugins = 0;
	for (auto const& entry : dirIterator)
	{
		if (entry.path().extension() == ".dll")
		{
			++numPlugins;
		}
	}

	Logging::PrintMessage(std::format("Found {} plugins:", numPlugins));

	dirIterator = std::filesystem::directory_iterator("Plugins");

	//Load all dll files in "./Plugins"
	for (auto const& entry : dirIterator)
	{
		auto file = entry.path();
		if (file.has_extension() && file.extension() == ".dll")
		{
			auto p = LoadPlugin(file);
			pluginInfos.emplace_back(p.Info);
			plugins.emplace_back(p.Handle);
		}
	}
}

PluginManager::~PluginManager()
{
	for (auto plugin : plugins)
	{
		auto f = Native::GetFunctionFromLibrary<Plugins::PluginUnload>(plugin, "PluginUnload");
		if (f != nullptr)
		{
			if (!f()) Logging::PrintMessage(std::format("PluginUnload() returned false! Handle {:x}", reinterpret_cast<intptr_t>(plugin)));
		}
	}
}

const PluginInfo PluginManager::GetPluginInfo(size_t index) const noexcept
{
	if (index >= pluginInfos.size()) return {};
	return pluginInfos[index];
}

const void* PluginManager::GetPluginHandle(size_t index) const noexcept
{
	if (index >= plugins.size()) return nullptr;
	return plugins[index];
}

std::vector<PluginInfo>::const_iterator PluginManager::begin() const noexcept
{
	return pluginInfos.begin();
}

std::vector<PluginInfo>::const_iterator PluginManager::end() const noexcept
{
	return pluginInfos.end();
}

PluginManager::PluginLoadResult PluginManager::LoadPlugin(const std::filesystem::path& pluginPath)
{
	auto p = Plugins::LoadPlugin(pluginPath);
	auto result = p.and_then([this](std::pair<Plugins::PluginInfo, void*> plugin) -> decltype(p)
		{
			pluginInfos.push_back(plugin.first);

			auto& [info, handle] = plugin;
			plugins.push_back(handle);

			Logging::PrintMessage(std::format("Loaded plugin {} ver {} handle 0x{:x}", info.Name, info.Version, reinterpret_cast<intptr_t>(handle)));

			auto numLoadedObjects = Plugins::LoadCustomObjectsFromLibHandle(handle);
			Logging::PrintMessage(std::format("Loaded {} custom object types from plugin {}", numLoadedObjects, info.Name));

			return plugin;
		}
	).or_else([&pluginPath](Plugins::PluginLoadingError err) -> decltype(p)
		{
			std::string msg = "Unknown error";
			switch (err)
			{
			case Plugins::PluginLoadingError::UnableToLoadPluginLibrary:
				msg = "Unable to load library.";
				break;
			case Plugins::PluginLoadingError::NotA3DRadSpacePlugin:
				msg = "Not a 3DRadSpace Plugin!\r\nFunction \"bool PluginMain()\" was not found!";
				break;
			case Plugins::PluginLoadingError::InitializationFunctionFailure:
				msg = "Plugin initialization failed!";
				break;
			default:
				break;
			}

			Logging::PrintWarning(std::format("Failed to load plugin at {}!\r\n{}", pluginPath.string(), msg));
			return std::unexpected(err);
		}
	);

	if (result.has_value())
	{
		auto& [info, handle] = result.value();
		return { handle, info, plugins.size() - 1 };

	}
	else
	{
		return { nullptr, {}, static_cast<size_t>(-1) };
	}
}

void PluginManager::UnloadPlugin(size_t index)
{
	if (index >= plugins.size()) return;
	auto plugin = plugins[index];
	auto f = Native::GetFunctionFromLibrary<Plugins::PluginUnload>(plugin, "PluginUnload");
	if (f != nullptr)
	{
		if (!f()) Logging::PrintMessage(std::format("PluginUnload() returned false! Handle {:x}", reinterpret_cast<intptr_t>(plugin)));
	}
	plugins.erase(plugins.begin() + index);
	pluginInfos.erase(pluginInfos.begin() + index);
}