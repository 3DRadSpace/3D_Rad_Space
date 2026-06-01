#include "pch.h"
#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Graphics/IVertexBuffer.hpp>
#include <Engine3DRadSpace/Graphics/IShaderCompiler.hpp>
#include "PerceptualHash.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Input;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Content;

class EmptyGame : public Game
{
	int numFrames = 0;
	int limNumFrames;
public:
	EmptyGame(int numFrames);

	void Update() override
	{
		Game::Update();

		++numFrames;
		if (numFrames >= limNumFrames)
		{
			Exit();
		}
	}
};

EmptyGame::EmptyGame(int numFrames) :
	Game("Empty Game", 800, 600),
	limNumFrames(numFrames)
{
}

TEST(EngineCoreTests, EmptyGameTest)
{
	EmptyGame g(0);
	g.Run();
	EXPECT_TRUE(true);
}

TEST(EngineCoreTests, EmptyGameTest5sec)
{
	EmptyGame g(60 * 5);
	g.Run();
	EXPECT_TRUE(true);
}