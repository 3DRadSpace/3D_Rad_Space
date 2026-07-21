#include "pch.h"

#include <Engine3DRadSpace/Games/Game.hpp>

#include <Engine3DRadSpace/Physics/Objects/FPCharacter.hpp>
#include <Engine3DRadSpace/Physics/Objects/RigidStatic.hpp>	
#include <Engine3DRadSpace/Physics/Objects/RigidDynamic.hpp>
#include <Engine3DRadSpace/Objects/Impl/Skinmesh.hpp>
#include <Engine3DRadSpace/Objects/Impl/Skybox.hpp>
#include <Engine3DRadSpace/Objects/Impl/SoundEffect.hpp>
#include <Engine3DRadSpace/Objects/ObjectList.hpp>

class MyGame : public Engine3DRadSpace::Game
{
public:
	MyGame() : Game("MyGame")
	{
		this->AppendScene("D:\\Projects\\3D_Rad_Space\\3DRadSpace\\Projects\\SoundEffect + EventOnKey demo.3drsp");
		//this->AppendScene("D:\\Projects\\3D_Rad_Space\\3DRadSpace\\Data\\Sounds\\memleaktest.3drsp");
	}

	bool once = false;

	void Update() override
	{
		Game::Update();

		if (Keyboard.IsKeyDown(Engine3DRadSpace::Input::Key::Space))
		{
			this->Objects->operator[](1)->Enable();
			once = true;
		}
	}

	~MyGame() override = default;
};

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	(void)hPrevInstance;
	(void)lpCmdLine;
	(void)nShowCmd;

	MyGame game;
	game.Run();
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	
	//WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);

	return RUN_ALL_TESTS();
}