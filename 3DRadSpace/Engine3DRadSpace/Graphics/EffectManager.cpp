#include "EffectManager.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Graphics;

EffectManager::EffectManager() : IService(nullptr)
{
}

Effect* EffectManager::Add(const std::string& name, std::unique_ptr<Effect>&& effect)
{
	_effects[name] = std::move(effect);
	return _effects[name].get();
}

IShader* EffectManager::Add(const std::string& name, std::unique_ptr<IShader>&& shader)
{
	_shaders[name] = std::move(shader);
	return _shaders[name].get();
}

Effect* EffectManager::GetEffect(const std::string& name)
{
	auto effect = _effects.find(name);
	if(effect != _effects.end())
	{
		return effect->second.get();
	}
	return nullptr;
}

IShader* EffectManager::GetShader(const std::string& name)
{
	auto shader = _shaders.find(name);
	if (shader != _shaders.end())
	{
		return shader->second.get();
	}
	return nullptr;
}