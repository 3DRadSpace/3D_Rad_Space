#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Native/Directory.hpp>

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

		if (path == "-d")
		{
			char filename[MAX_PATH] = "";

			OPENFILENAMEA ofn{};
			ofn.lStructSize = sizeof(ofn);
			ofn.Flags = OFN_FILEMUSTEXIST;
			ofn.lpstrFilter = "3DRadSpace Project (*.3drsp)\0*.3drsp\0\0";
			ofn.lpstrFile = filename;
			ofn.hInstance = hInstnace;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFileTitle = const_cast<char*>("Open a 3DRadSpace Project to be played");

			if (GetOpenFileNameA(&ofn))
			{
				projectPath = ofn.lpstrFile;
				Engine3DRadSpace::Native::SetDefaultWorkingDirectory();
				
				break;
			}
		}
	}

	MyGame game("My Game", projectPath);
	game.Run();
	return 0;
}