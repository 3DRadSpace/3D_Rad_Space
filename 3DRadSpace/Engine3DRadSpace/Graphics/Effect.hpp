#pragma once
#include "IGraphicsDevice.hpp"
#include "IShader.hpp"
#include "ShaderType.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents references to N shaders, all making up a pipeline.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Effect
	{
	protected:
		IGraphicsDevice* _device;
		std::vector<IShader*> _shaders;
	public:
		Effect(
			IGraphicsDevice* device, 
			std::span<IShader*> shaders
		);

		Effect(const Effect &p) = delete;
		Effect(Effect&& p) noexcept = default;

		Effect &operator =(const Effect &p) = delete;
		Effect& operator =(Effect&& p) noexcept = default;
		
		/// <summary>
		/// Sets all the effects.
		/// </summary>
		/// <returns>Number of effects succesfully set.</returns>
		int SetAll() const noexcept;

		bool Set(int index) const noexcept;
	
		template<typename T>
		void Set(const std::string& name, const T& value) noexcept
		{
			for (auto shader : _shaders)
			{
				shader->Set<T>(name, value);
			}
		}

		template<typename T>
		void Set(const std::string& name, const T& value, int shaderIndex) noexcept
		{
			_shaders[shaderIndex]->Set<T>(name, value);
		}

		void SetData(void* data, size_t size, int cbufferID, int shaderID);
		void SetData(void* data, size_t size, int cbufferID);

		template<typename T>
		void SetData(T* data, int cbufferID, int shaderID)
		{
			SetData(data, sizeof(T), cbufferID, shaderID);
		}

		template<typename T>
		void SetData(T* data, int cbufferID)
		{
			SetData(static_cast<void*>(data), sizeof(T), cbufferID);
		}

		void SetTexture(ITexture2D* texture, int idx) noexcept;
		void SetTexture(ITexture2D* texture, int textureID, int shaderID) noexcept;
		void SetSampler(ISamplerState* sampler, int idx) noexcept;
		void SetSampler(ISamplerState* sampler, int samplerID, int shaderID) noexcept;

		IShader* operator[](size_t idx) const;

		~Effect() = default;
	};
}