#pragma once
#include "Libs.hpp"
#include "GraphicsDevice.hpp"
#include <memory>

namespace Engine3DRadSpace
{
	class GameWindow
	{
	public:
		GameWindow(const char* title,unsigned width = 800, unsigned height = 600);
		std::unique_ptr<GraphicsDevice> GraphicsDevice;
	};
}