#include <Engine3DRadSpace/Games/Game.hpp>

class MyGame : public Engine3DRadSpace::Game
{
public:
	MyGame(const std::string& title, const std::filesystem::path& assetPath, size_t width = 800, size_t height = 600)
		: Engine3DRadSpace::Game(title, width, height)
	{
		if(!assetPath.empty())
			AppendScene(assetPath);
	}

	~MyGame() override = default;
};

int WinMain(HINSTANCE hInstnace, HINSTANCE hPrevInstnace, LPSTR lpCmdLine, int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstnace);

	std::filesystem::path projectPath;

	std::string cmdArgs(lpCmdLine);
	for (const auto token : std::views::split(cmdArgs, "\""))
	{
		std::string path(token.begin(), token.end());
		if (path[0] == '"') path.erase(0, 1);
		if (path[path.length() - 1] == '"') path.erase(path.length() - 1, 1);

		if (std::filesystem::exists(path))
		{
			projectPath = path;
		}
	}

	MyGame game("My Game", projectPath);
	game.Run();
	return 0;
}