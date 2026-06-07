#include "NullGame.hpp"

using namespace Engine3DRadSpace::Games;

void NullGame::Exit()
{	
}

bool NullGame::WasInitialized() const noexcept
{
	return true;
}

bool NullGame::WasLoaded() const noexcept
{
	return true;
}

bool NullGame::IsEditor() const noexcept
{
	return true;
}

void NullGame::AppendScene(const std::filesystem::path& path)
{
}