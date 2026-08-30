#pragma once
#include "EditorPlugin.hpp"
#include "../Core/IService.hpp"

namespace Engine3DRadSpace::Plugins
{
	class PluginManager : public IService
	{
	private:
		std::vector<void*> plugins;
		std::vector<PluginInfo> pluginInfos;
	public:
		PluginManager(IGame* owner);

		PluginManager(const PluginManager&) = delete;
		PluginManager& operator=(const PluginManager&) = delete;

		PluginManager(PluginManager&&) noexcept = default;
		PluginManager& operator=(PluginManager&&) noexcept = default;

		const PluginInfo GetPluginInfo(size_t index) const noexcept;
		const void* GetPluginHandle(size_t index) const noexcept;

		std::vector<PluginInfo>::const_iterator begin() const noexcept;
		std::vector<PluginInfo>::const_iterator end() const noexcept;

		~PluginManager();
	};
}