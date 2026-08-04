#include "ShaderCompiler.hpp"
#include "GraphicsDevice.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"
#include "DomainShader.hpp"
#include "GeometryShader.hpp"
#include "HullShader.hpp"
#include "ShaderBase.hpp"
#include "../../Logging/Warning.hpp"
#include "../../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;
using namespace Engine3DRadSpace::Graphics::DirectX11;
using namespace Engine3DRadSpace::Logging;

ShaderCompiler::ShaderCompiler(GraphicsDevice *device) :
	IShaderCompiler(),
	_device(device)
{
}


std::string ShaderCompiler::shaderID_file(const ShaderDescFile* fileDesc)
{
	return fileDesc->FilePath.string() + "::" + fileDesc->EntryPoint;
}

std::string ShaderCompiler::shaderID(const ShaderDesc* desc)
{
	if (desc == nullptr) return "";

	if (auto descFile = dynamic_cast<const ShaderDescFile*>(desc); descFile != nullptr)
	{
		return shaderID_file(descFile);
	}
	else if (auto descSrc = dynamic_cast<const ShaderDescSource*>(desc); descSrc != nullptr)
	{
		return descSrc->SourceCode;
	}
	else return "???";
}

ShaderCompiler::CompileOutput ShaderCompiler::Compile(const ShaderDesc* desc)
{
	auto return_fail = [](const std::string& msg)
		{
			return std::make_pair<IShader*, ShaderCompilationResult>(
				nullptr,
				ShaderCompilationResult
				{
					msg,
					false,
					""
				}
			);
		};

	auto return_already_compiled = [&](const ShaderDescFile* fileDesc)
	{
		auto id = shaderID_file(fileDesc);
		if (auto shader = _manager->GetShader(id); shader != nullptr)
		{
			return std::make_pair<IShader*, ShaderCompilationResult>(
				(IShader*)shader,
				ShaderCompilationResult
				{
					"Already registered",
					true, 
					id
				}
			);
		}
		else return std::make_pair<IShader*, ShaderCompilationResult>(
			nullptr, 
			ShaderCompilationResult
			{
				"",
				false,
				""
			}
		);
	};

	auto return_already_compiled2 = [&](const ShaderDescSource* sourceDesc)
	{
		if (auto shader = _manager->GetShader(sourceDesc->SourceCode); shader != nullptr)
		{
			return std::make_pair<IShader*, ShaderCompilationResult>(
				(IShader*)shader,
				ShaderCompilationResult
				{
					"Already registered",
					true,
					sourceDesc->SourceCode
				}
			);
		}
		else return std::make_pair<IShader*, ShaderCompilationResult>(
			nullptr,
			ShaderCompilationResult
			{
				"",
				false,
				""
			}
		);
	};

	auto make_shader_FileDesc = []<typename ShaderType>(
		std::unique_ptr<IShader>& ptr,
		GraphicsDevice* device,
		const ShaderDescFile* fileDesc
		) -> void
		{
			ptr.reset(new ShaderType(
				device,
				fileDesc->FilePath,
				fileDesc->EntryPoint.c_str(),
				fileDesc->FeatureLevel
			));
		};

	auto make_shader_SourceDesc = []<typename ShaderType>(
		std::unique_ptr<IShader> &ptr,
		GraphicsDevice * device,
		const ShaderDescSource * sourceDesc
		) -> void
	{
		ptr.reset(new ShaderType(
			device,
			sourceDesc->SourceCode,
			sourceDesc->EntryPoint.c_str(),
			sourceDesc->FeatureLevel
		));
	};

	if (desc == nullptr) return return_fail("Null description");

	ShaderCompilationResult result;
	std::unique_ptr<IShader> ptr;
	std::string shaderName;

	try
	{
		if (auto fileDesc = dynamic_cast<const ShaderDescFile*>(desc); fileDesc != nullptr)
		{
			if (auto d = return_already_compiled(fileDesc); d.second.Succeded == true)
			{
				return d;
			}

			switch (fileDesc->Type)
			{
			case ShaderType::Vertex:
			{
				make_shader_FileDesc.template operator()<DirectX11::VertexShader>(ptr, _device, fileDesc);
				break;
			}
			case ShaderType::Fragment:
			{
				make_shader_FileDesc.template operator()<DirectX11::FragmentShader>(ptr, _device, fileDesc);
				break;
			}
			case ShaderType::Geometry:
			{
				make_shader_FileDesc.template operator()<DirectX11::FragmentShader>(ptr, _device, fileDesc);
				break;
			}
			case ShaderType::Hull:
			{
				make_shader_FileDesc.template operator()<DirectX11::HullShader>(ptr, _device, fileDesc);
				break;
			}
			case ShaderType::Domain:
			{
				make_shader_FileDesc.template operator()<DirectX11::DomainShader>(ptr, _device, fileDesc);
				break;
			}
			default:
				return return_fail("Unsupported shader type.");
			}
		}
		else if (auto sourceDesc = dynamic_cast<const ShaderDescSource*>(desc); sourceDesc != nullptr)
		{
			if (auto d = return_already_compiled2(sourceDesc); d.second.Succeded == true)
			{
				return d;
			}

			switch (sourceDesc->Type)
			{
			case ShaderType::Vertex:
			{
				make_shader_SourceDesc.template operator()<DirectX11::VertexShader>(ptr, _device, sourceDesc);
				break;
			}
			case ShaderType::Fragment:
			{
				make_shader_SourceDesc.template operator()<DirectX11::FragmentShader>(ptr, _device, sourceDesc);
				break;
			}
			case ShaderType::Geometry:
			{
				make_shader_SourceDesc.template operator()<DirectX11::GeometryShader>(ptr, _device, sourceDesc);
				break;
			}
			case ShaderType::Hull:
			{
				make_shader_SourceDesc.template operator()<DirectX11::HullShader>(ptr, _device, sourceDesc);
				break;
			}
			case ShaderType::Domain:
			{
				make_shader_SourceDesc.template operator()<DirectX11::DomainShader>(ptr, _device, sourceDesc);
				break;
			}
			default:
				return return_fail("Unsupported shader type.");
			}
		}

		auto id = shaderID(desc);

		auto pShader = ptr.get();
		_manager->Add(id, std::move(ptr));

		return std::make_pair(
			pShader,
			ShaderCompilationResult
			{
				pShader->GetCompilationErrorsAndWarnings(),
				true,
				shaderID(desc)
			}
		);
	}
	catch (const Exception& e)
	{
		Logging::PrintWarning(e.What());
		return return_fail(e.what());
	}
}

ShaderCompiler::EffectCompileOutput ShaderCompiler::CompileEffect(std::span<ShaderDesc*> descs)
{
	std::vector<IShader*> shaders;
	std::string id;

	for (ShaderDesc *desc : descs)
	{
		auto c = Compile(desc);
		if (c.second.Succeded && c.first != nullptr)
		{
			shaders.emplace_back(c.first);
			id += shaderID(desc) + " ";
		}
	}

	if (shaders.empty())
	{
		return std::make_pair<Effect*, ShaderCompilationResult>(
			nullptr,
			ShaderCompilationResult{
				.Log = "Empty effect",
				.Succeded = false,
				.Identifier = ""
			}
		);
	}

	if (auto effect = _manager->GetEffect(id); effect != nullptr)
	{
		return std::make_pair<Effect*, ShaderCompilationResult>(
			(Effect*)effect,
			ShaderCompilationResult{
				.Log = "",
				.Succeded = true,
				.Identifier = id
			}
		);
	}

	Effect effect(_device, shaders);
	auto r = _manager->Add(id, std::make_unique<Effect>(std::move(effect)));
	
	return std::make_pair<Effect*, ShaderCompilationResult>(
		(Effect*)r,
		ShaderCompilationResult{
			.Log = "",
			.Succeded = true,
			.Identifier = id
		}
	);
}