#include "SourceGenerator.hpp"
#include "ProjectBuilder.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

std::unordered_map<std::string, int> dict =
{
	{"-h", 1},
	{"--help", 1},
	{"/?", 1},
	{"-v", 2},
	{"/v", 2},
	{"--version", 2},
	{"-o", 3},
	{"/o", 3},
	{"-output", 3},
	{"--checkcompiler", 4},
	{"--compiler", 4},
	{"-c", 4},
	{"/c", 4},
	{"-r", 5},
	{"/r", 5},
	{"--reset", 5},
	{"--play",5},
	{"-p", 5},
	{"/p", 5},
	{"--name",6},
	{"-n",6},
	{"/n",6},
	{"--clean", 7},
	{"-c", 7},
	{"/c", 7},
	{"-e", 8},
	{"/e",8},
	{"--entry", 8}
	//{"--debug", 6},
	//{"-d", 6},
	//{"/d", 6}
};

std::unordered_map<std::string, int> file_type =
{
	//C++ Source files.
	{".cpp", 1},
	{".cxx", 1},
	{".c++", 1},

	//C++ header files
	{".hpp", 2},
	{".hxx", 2},
	{".h++", 2},
	//C source file
	{".c", 3}, 
	//C header file
	{".h", 4 },

	//C# source files.
	{".cs", 5},
	//Icon
	{".ico", 6},
	//3DRadSpace scene project
	{".3drsp", 7},
	//Resource file
	{".rc", 8}
};

auto LoadCompilerCache() -> std::optional<Compiler>
{
	if(!std::filesystem::exists("compiler_cache.json")) return std::nullopt;

	std::ifstream cache("compiler_cache.json");
	if(!cache.good())
	{
		std::println("Failed to open compiler cache!");
		return std::nullopt;
	}

	std::println("Found cached envoirement settings...");

	nlohmann::json j;
	cache >> j;

	if(j.empty())
	{
		std::println("Cached compiler settings were erased.");
		return std::nullopt;
	}

	std::filesystem::path devenv = j["devenv"].get<std::string>();
	if(!devenv.empty())
	{
		if(std::filesystem::exists(devenv))
		{
			std::println("Found Visual Studio devenv: {}", devenv.string());

			return Compiler
			{
				.CompilerType = Compiler::Type::MSVC,
				.Path = devenv.string()
			};
		}
		else
		{
			std::println("[WARNING]Cached devenv path doesn't exist.");
		}
	}

	std::filesystem::path clang = j["clang"].get<std::string>();
	if(!clang.empty())
	{
		if(std::filesystem::exists(clang))
		{
			std::println("Found Clang: {}", clang.string());
			return Compiler
			{
				.CompilerType = Compiler::Type::Clang,
				.Path = clang.string()
			};
		}
		else
		{
			std::println("[WARNING]Cached clang path doesn't exist.");
		}
	}
#ifdef _LINUX
	std::filesystem::path gcc = j["gcc"].get<std::string>();
	if(!gcc.empty())
	{
		if(std::filesystem::exists(gcc))
		{
			std::println("Found GCC: {}", gcc.string());
			return Compiler
			{
				.CompilerType = Compiler::Type::GCC,
				.Path = gcc.string()
			};
		}
		else
		{
			std::println("[WARNING]Cached gcc path doesn't exist.");
		}
	}
#endif
	std::println("[WARNING]Cached compiler settings are invalid.");
	cache.close();
	std::filesystem::remove("compiler_cache.json");
	return std::nullopt;
}

auto startProject(std::filesystem::path& outDir, const std::string& projectName)
{
#ifdef _WIN32
	//SECURITY_ATTRIBUTES sa;
	//sa.nLength = sizeof(sa);
	//sa.bInheritHandle = TRUE;
	//sa.lpSecurityDescriptor = nullptr;

	//STARTUPINFOA si{};
	//si.cb = sizeof(si);
	//si.dwFlags = 0;

	//PROCESS_INFORMATION pi{};

	auto exePath = (outDir / std::format("x64/Release/{}.exe", projectName)).string();
	auto runningFolder = (outDir / "x64/Release/").string();
	//auto r = CreateProcessA(
	//	exePath.c_str(),
	//	nullptr,
	//	&sa,
	//	&sa,
	//	TRUE,
	//	0,
	//	nullptr,
	//	runningFolder.c_str(),
	//	&si,
	//	&pi
	//);

	return reinterpret_cast<INT_PTR>(ShellExecuteA(
		nullptr,
		"open",
		exePath.c_str(),
		"",
		runningFolder.c_str(),
		SW_MAXIMIZE
	)) > 32;
#endif
#ifdef _LINUX

#endif
}

auto main(int argc, char** argv) -> int
{
	std::println("3DRadSpace Compiler v0.1.0a\n");

	std::vector<std::filesystem::path> files;
	std::filesystem::path outputFolder;

	bool wasOutputSpecified = false;
	bool playProject = false;
	bool rebuild = false;

	ProjectInfo info;
	info.Name = "MyGame";
	info.Output = "MyGame/";

	for(int i = 1; i < argc; i++)
	{
		switch(dict[argv[i]])
		{
			case 1:
				std::println("Tool that invokes a C++ compiler and generates a game from project and source files.");
				std::println("Arguments");
				std::println("Help : -h --help or /?");
				std::println("Version : -v --version or /v");
				std::println("Output: -o <output folder> or --output <output folder> or /o <output folder>");
				std::println("Check compiler: --compiler, --checkcompiler or -c or /c");
				std::println("Reset compiler cache: --reset or -r or /r");
				std::println("Clean build: --clean or -c or /c ");
				std::println("Run project after build: --play or -p or /p ");
				std::println("Project name: --name <name> or -n <name> or /n <name>");
				std::println("Playtest single scene: --test <3drsp filename> or -t <filename> or /t <filename>");
				//std::println("To attach a debugger: --debug or -d or /d");
				std::println("");
				std::println("To build a 3DRadSpace project:");
				std::println("Use: 3DRadSpaceCompiler.exe -o <output folder> <source files> [-p] [-n <project name>]");
				//std::println("");
				//std::println("To play and attach a debugger:");
				//std::println("Use: 3DRadSpaceCompiler.exe -d <output folder>");
				return 0;
			case 2:
				return 0;
			case 3:
				if(i + 1 < argc)
				{
					outputFolder = std::filesystem::path(argv[i + 1]);
					i += 1;
				}
				else
					std::println("[WARNING] {} must specify output", argv[i]);
				break;
			case 4:
			{
				auto compiler = LoadCompilerCache();
				if(!compiler.has_value())
				{
					compiler = FindCompiler();
				}
				if(compiler.has_value())
				{
					SaveCompilerCache(compiler.value());
					compiler->Print();
					return 0;
				}
				else
				{
					std::println("[STOP] No compiler found.");
					return 0;
				}
				break;
			}
			case 5:
				playProject = true;
				break;
			case 6:
			{
				if(i + 1 < argc)
				{
					info.Name = std::string(argv[++i]);
				}
				else
				{
					info.Name = "MyGame";
					std::println("[INFO] {} must specify project name. Using \"MyGame\" as default.", argv[i-1]);
				}
				break;
			}
			case 7:
				rebuild = true;
				break;
			case 8:
				if(i + 1 < argc)
				{
					info.EntryProject = std::filesystem::path(argv[++i]);
				}
				else
				{
					std::println("[STOP] {} Must specify filename.", argv[i - 1]);
				}
				break;
			default:
				if(!std::filesystem::exists(argv[i]))
				{
					std::println("[WARNING] Specified file {} doesn't exist!", argv[i]);
				}
				else files.emplace_back(argv[i]);
				break;
		}
	}

	if(files.empty() && info.EntryProject.empty())
	{
		std::println("[STOP] No files provided.");
		return -1;
	}

	if(!info.Output.empty())
	{
		std::println("[INFO] Output folder not specified. Using current directory.");
		outputFolder = std::filesystem::current_path() / info.Name;

		if(std::filesystem::exists(outputFolder) && rebuild)
		{
			try
			{
				//Erase folder with all of its contents.
				std::filesystem::remove_all(outputFolder);
				return 0;
			}
			catch(const std::filesystem::filesystem_error& err)
			{
				std::print("[ERROR] {}", err.what());
				return err.code().value();
			}
		}
		//Recreate folder
		std::filesystem::create_directory(outputFolder);
	}
	else if(rebuild)
	{
		std::println("[STOP]Must specify folder.");
		return -1;
	}

	int numSteps = 4;
	if(playProject) numSteps += 1;

	std::println("3DRadSpace Compiler v0.1.0a");
	
	std::println("[1/{}] Checking project files:", numSteps);
	for(auto& file : files)
	{
		std::string type;
		switch(file_type[file.extension().string()])
		{
			case 1:
				type = "C++ source file";
				break;
			case 2:
				type = "C++ header file";
				break;
			case 3: 
				type = "C source file";
				break;
			case 4:
				type = "C header file";
				break;
			case 5:
				type = "C# source file";
				break;
			case 6:
				type = "Icon resource";
				break;
			case 7:
				type = "3DRadSpace Scene";
				break;
			case 8:
				type = "Resource file";
				break;
			default:
				type = "Unknown type";
				break;

		}
		std::println("- {}: {}", type, file.string());
	}

	std::println("[2/{}] Checking envoirement...", numSteps);

	std::optional<Compiler> compiler = LoadCompilerCache();
	if(compiler.has_value()) goto generate;

	compiler = FindCompiler();
	if(!compiler.has_value())
	{
		return -1;
	}

	SaveCompilerCache(compiler.value());
	std::println("[INFO] Caching compiler path");
generate:
	std::println("[3/{}] Generating project files...", numSteps);
	GenerateProject(info, files, compiler->CompilerType);
//Build
	std::println("[4/{}] Building project...", numSteps);

	auto printBuildMsg = [](bool r, const char* name)
	{
		if(r == 0) std::println("[SUCCESS]Finished building.");
		else std::println("[ERROR] Failed to build project with {}.", name);
	};

	switch(compiler->CompilerType)
	{
		case Compiler::Type::MSVC:
			printBuildMsg(MSVC_Build(info, compiler->Path), "MSVC");
			break;
		case Compiler::Type::GCC:
			printBuildMsg(GCC_Build(info, compiler->Path), "GCC");
			break;
		case Compiler::Type::Clang:
			printBuildMsg(Clang_Build(info, compiler->Path), "Clang");
			break;
		default:
			std::println("[STOP] Unknown compiler type.");
			return -1;
	}

	//TODO Parse project files, actually copy only necessary assets.
	
	auto fnCopy = [](const std::filesystem::path& from, const std::filesystem::path& to)
	{
		std::filesystem::copy(
			from,
			to,
			std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
		);
	};

	std::println("Copying Assets folder.");
	try
	{
		fnCopy(".\\\\Data\\", std::filesystem::canonical(info.Output) / "Data");
		fnCopy(".\\\\Data\\", std::filesystem::canonical(info.Output) / "x64" / "Release" / "Data");
	}
	catch(const std::filesystem::filesystem_error& e)
	{
		std::println("Copying assets failed {}", e.what());
	}

	std::println("Copying Plugins folder.");
	try
	{
		fnCopy(".\\\\Plugins\\", std::filesystem::canonical(info.Output) / "Plugins");
		fnCopy(".\\\\Plugins\\", std::filesystem::canonical(info.Output) / "x64" / "Release" / "Plugins");
	}
	catch(const std::filesystem::filesystem_error& e)
	{
		std::println("Copying plugins failed {}", e.what());
	}

	if(playProject)
	{
		std::println("[5/{}] Starting project...", numSteps);
		if(startProject(outputFolder, info.Name) == false)
		{
			std::println("[ERROR] Failed to start the project...");
			std::println("[ERROR] This could be because of compilation errors.");
			return -2;
		}
	}

	std::println("Finished.");

	return 0;
}