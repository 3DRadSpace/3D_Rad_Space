#pragma once
#include "../Graphics/Effect.hpp"
#include "../Tag.hpp"

namespace Engine3DRadSpace::Content
{
	template<typename S>
	concept ShaderCollection = std::is_base_of<Graphics::Shaders::Effect,S>::value
		&& requires(GraphicsDevice* device)
	{
		S(device); //Shaders must be constructible from the graphics device.
	};

	class DLLEXPORT ShaderManager
	{
		static std::unordered_map<size_t, std::shared_ptr<Graphics::Shaders::Effect>> _shaders;
	public:
		ShaderManager() = delete;
		ShaderManager(ShaderManager &) = delete;
		ShaderManager(ShaderManager &&) noexcept = delete;

		ShaderManager &operator=(ShaderManager &) = delete;
		ShaderManager &operator=(ShaderManager &&) noexcept = delete;

		template<ShaderCollection S>
		static std::shared_ptr<S> LoadShader(GraphicsDevice *device);

		template<ShaderCollection S>
		static S *GetShader(Tag<S> t);

		~ShaderManager() = default;

		static void ReleaseAll();
	};










	template<ShaderCollection S>
	inline std::shared_ptr<S> ShaderManager::LoadShader(GraphicsDevice *device)
	{
		auto f = _shaders.find(typeid(S).hash_code());

		if(f == _shaders.end())
		{
			std::shared_ptr<S> ptr;
			ptr.reset(new S(device));

			_shaders.insert({typeid(S).hash_code(), ptr});
			return ptr;
		}
		else return std::static_pointer_cast<S>(f->second);
	}

	template<ShaderCollection S>
	inline S *ShaderManager::GetShader(Tag<S> t)
	{
		return _shaders[typeid(S).hash_code()];
	}
}