#include "SkinmeshGizmo.hpp"
#include "../../Graphics/IGraphicsDevice.hpp"
#include "../../Graphics/IRasterizerState.hpp"
#include "../../Games/Game.hpp"
#include "../../Graphics/IShaderCompiler.hpp"
#include "../../Graphics/IGraphicsCommandList.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Logging;
using namespace Engine3DRadSpace::Math;
using namespace Engine3DRadSpace::Objects;
using namespace Engine3DRadSpace::Objects::Gizmos;

Gizmo<Skinmesh>::Gizmo() :
	_highlightEffect(nullptr)
{
	Allow3DRendering = true;
	Allow2DRendering = false;
}

void Gizmo<Skinmesh>::Load()
{
	if(Object == nullptr) return;

	auto skinmesh = static_cast<Skinmesh*>(Object);
	_wasLoaded = skinmesh->GetModel() != nullptr;

	auto device = skinmesh->GetGraphicsDeviceHandle();

	if(_wireframe_RasterizerState == nullptr)
	{
		_wireframe_RasterizerState = device->CreateRasterizerState_Wireframe();
	}

	if(_depthStencilState == nullptr)
	{
		_depthStencilState = device->CreateDepthStencilState(
			true,
			DepthWriteMask::All,
			ComparisonFunction::LessEqual,
			false,
			1,
			1,
			FaceOperation{
				.StencilFail = StencilOperation::Keep,
				.DepthFail = StencilOperation::Keep,
				.PassOp = StencilOperation::Keep,
				.Function = ComparisonFunction::Always,
			},
			FaceOperation{
				.StencilFail = StencilOperation::Keep,
				.DepthFail = StencilOperation::Keep,
				.PassOp = StencilOperation::Keep,
				.Function = ComparisonFunction::Always,
			}
		);
	}

	if (this->_highlightEffect == nullptr)
	{
		constexpr const char* highlightMeshPath = "Data//Shaders//HighlightMesh.hlsl";

		auto vsHighlight = ShaderDescFile(
			highlightMeshPath,
			"VS_Main",
			ShaderType::Vertex
		);

		auto psHighlight = ShaderDescFile(
			highlightMeshPath,
			"PS_Main",
			ShaderType::Fragment
		);

		std::array<ShaderDesc*, 2> highlightDesc = { &vsHighlight, &psHighlight };

		auto compileResult = device->ShaderCompiler()->CompileEffect(highlightDesc);
		if (compileResult.second.Succeded)
		{
			_highlightEffect = compileResult.first;
		}
		else throw Exception("Failed to compile Highlight effect for Skinmesh gizmo!" + compileResult.second.Log);
	}

	if(_wasLoaded) return;

	Object->Load();
}

void Gizmo<Skinmesh>::Load(const std::filesystem::path& path)
{
}

void Gizmo<Skinmesh>::Draw3D()
{
	if(Object != nullptr)
	{
		auto skinmesh = static_cast<Skinmesh*>(Object);
		if(skinmesh != nullptr)
		{
			skinmesh->Draw3D();
		}

		if(Selected)
		{
			if(skinmesh->GetModel() == nullptr) return;

			auto device = skinmesh->GetGraphicsDeviceHandle();		
			auto oldRasterizerState = device->GetRasterizerState();
			auto oldDepthState = device->GetDepthStencilState();
			auto wireframe = static_cast<IRasterizerState*>(_wireframe_RasterizerState.get());
			auto cmd = device->ImmediateContext();

			//cmd->UnbindDepthBuffer();
			cmd->SetRasterizerState(wireframe);
			cmd->SetDepthStencilState(_depthStencilState.get(), 0);

			auto game = static_cast<Game*>(skinmesh->GetGame());
			
			auto highlightColor = Color(1.0f, 0.5f, 0.0f, 1.0f);
			_highlightEffect->SetData<Color>(&highlightColor, 1);

			skinmesh->GetModel()->DrawEffect(
				_highlightEffect,
				skinmesh->GetModelMatrix() * game->View * game->Projection
			);

			//cmd->SetRenderTargetAndDepth(nullptr, nullptr);
			cmd->SetRasterizerState(oldRasterizerState.get());
			cmd->SetDepthStencilState(oldDepthState.get(), 0);
		}
	}
}

void Gizmo<Skinmesh>::Draw2D()
{
}

void Gizmo<Skinmesh>::Update()
{
}