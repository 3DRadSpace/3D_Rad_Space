#include "ShaderManager.hpp"

using namespace Engine3DRadSpace::Content;
using namespace Engine3DRadSpace::Graphics::Shaders;

std::unordered_map<size_t, std::shared_ptr<ShaderPipeline>> ShaderManager::_shaders;

void Engine3DRadSpace::Content::ShaderManager::ReleaseAll()
{
	for(auto &[id, shader] : _shaders)
	{
		shader.reset();
	}
}
