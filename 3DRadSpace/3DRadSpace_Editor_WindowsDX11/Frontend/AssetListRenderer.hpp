#pragma once
#include "AssetRenderer.hpp"
#include <Engine3DRadSpace/Content/ContentManager.hpp>
#include <Engine3DRadSpace/Games/Game.hpp>
#include "Controls\Dialog.hpp"

class AssetListRenderer
{
	std::unique_ptr<Engine3DRadSpace::Graphics::IGraphicsDevice> _device;
	HWND _renderWindow;
	HINSTANCE _hInstance;
public:
	AssetListRenderer(HWND owner, HINSTANCE instance, Engine3DRadSpace::Content::ContentManager *content);
	AssetListRenderer(AssetListRenderer &) = delete;
	AssetListRenderer(AssetListRenderer &&) = delete;

	AssetListRenderer operator=(AssetListRenderer &) = delete;
	AssetListRenderer operator=(AssetListRenderer &&) = delete;

	template<Engine3DRadSpace::Content::AssetType T>
	bool RenderAsset(const std::string& imagePath, const std::filesystem::path &assetPath)
	{
		auto cmd = _device->ImmediateContext();

		cmd->SetViewport();
		cmd->Clear(Engine3DRadSpace::Math::Colors::Gray);

		std::unique_ptr<T> asset = std::make_unique<T>(_device.get(), assetPath);

		bool r = AssetRenderer<T>(_device.get(), imagePath, asset.get());
		return r;
	}

	~AssetListRenderer();
};