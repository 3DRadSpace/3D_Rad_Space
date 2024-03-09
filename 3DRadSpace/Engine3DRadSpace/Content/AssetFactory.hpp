#pragma once
#include "Asset.hpp"
#include "../IGraphicsDevice.hpp"
#include "../Audio/AudioEngine.hpp"
#include "../Physics/PhysicsEngine.hpp"
#include "../Game.hpp"

namespace Engine3DRadSpace::Content
{
	class AssetFactory
	{
	private:
		GraphicsDevice* _device;
		Audio::AudioEngine* _audio;
		Physics::PhysicsEngine* _physics;
	public:
		AssetFactory(Game* game);

		AssetFactory(const AssetFactory&) = delete;
		AssetFactory(AssetFactory&&) = delete;

		AssetFactory& operator=(const AssetFactory&) = delete;
		AssetFactory& operator=(AssetFactory&&) = delete;

		template<AssetType T, typename ...Args>
		std::unique_ptr<T> Create(const std::filesystem::path& path, Args&& ...args)
		{
			using namespace Engine3DRadSpace::Audio;
			using namespace Engine3DRadSpace::Graphics;
			using namespace Engine3DRadSpace::Physics;

			//can be constructed from a GraphicsDevice
			if constexpr (std::is_constructible_v<T, GraphicsDevice*, const std::filesystem::path&>)
			{
				return std::make_unique<T>(_device, path, std::forward<Args>(args)...);
			}

			//can be constructed from a AudioEngine
			else if constexpr (std::is_constructible_v<T, AudioEngine*, const std::filesystem::path&>)
			{
				return std::make_unique<T>(_audio, path, std::forward<Args>(args)...);
			}

			//can be constructed from a PhysicsEngine
			else if constexpr (std::is_constructible_v<T, PhysicsEngine*, const std::filesystem::path&>)
			{
				return std::make_unique<T>(_physics, path, std::forward<Args>(args)...);
			}

			//We don't consider assets that need to be constructed from multiple abstraction layers (either GraphicsDevice, AudioEngine, PhysicsEngine, et cetara...)
		}
	};
}