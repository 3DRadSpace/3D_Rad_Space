#pragma once
#include "IGame.hpp"

namespace Engine3DRadSpace::Games
{
	/// <summary>
	/// A dummy game class that does nothing. Used for testing and rendering assets in editor.
	/// </summary>
	class E3DRSP_CORE_EXPORT NullGame : public IGame
	{
	public:
		NullGame() = default;
		NullGame(NullGame&) = delete;
		NullGame(NullGame&&) = delete;

		NullGame& operator=(NullGame&) = delete;
		NullGame& operator=(NullGame&&) = delete;

		void Exit() override;
		bool WasInitialized() const noexcept override;
		bool WasLoaded() const noexcept override;
		bool IsEditor() const noexcept override;
		void AppendScene(const std::filesystem::path& path) override;
	};
}