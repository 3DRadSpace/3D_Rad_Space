#include "pch.h"
#include <Engine3DRadSpace/Games/Game.hpp>
#include <Engine3DRadSpace/Graphics/IGraphicsDevice.hpp>
#include <Engine3DRadSpace/Graphics/IShaderCompiler.hpp>
#include <Engine3DRadSpace/Logging/Exception.hpp>

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

class TestGame : public Game
{
	Effect *_effect;
public:
	TestGame() : 
		Game("shader compile tests"),
		_effect(nullptr)
	{
	}

	void Initialize() override
	{
		//Compile test shader
		std::string_view shaderPath = "Data//Shaders//PickInfo.hlsl";

		ShaderDescFile vs_trivial(shaderPath, "VS_Main", ShaderType::Vertex);
		ShaderDescFile ps_trivial(shaderPath, "PS_Main", ShaderType::Fragment);

		std::array<ShaderDesc*, 2> shaderOne = { &vs_trivial, &ps_trivial };

		_effect = Device->ShaderCompiler()->CompileEffect(shaderOne).first; //If failed, should throw an exception

		if (_effect == nullptr) throw Logging::Exception("Failed to compile the effect."); //Or this...
	}

	Effect* Get()
	{
		return _effect;
	}
};

TEST(ShaderReflectionTests, ConstantBufferVariables)
{
	TestGame game;
	game.Initialize();

	auto variables = game.Get()->operator[](0)->GetVariables();

	EXPECT_EQ(variables[0]->FieldName(), "matWorldViewProj");
	EXPECT_EQ(variables[0]->TypeSize(), sizeof(Math::Matrix4x4));

	EXPECT_EQ(variables[1]->FieldName(), "ID");
	EXPECT_EQ(variables[1]->TypeSize(), sizeof(unsigned));
}