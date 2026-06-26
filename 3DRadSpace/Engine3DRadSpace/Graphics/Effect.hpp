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

		/// <summary>
		/// Sets the shader at the given index.
		/// </summary>
		/// <param name="index">Index of the shader to set.</param>
		/// <returns>True if the shader was successfully set, false otherwise.</returns>
		bool Set(int index) const noexcept;
	
		/// <summary>
		/// Sets the variable with the given name to the given value in all shaders.
		/// </summary>
		/// <typeparam name="T">Type of the variable to set.</typeparam>
		/// <param name="name">Name of the variable to set.</param>
		/// <param name="value">Value to set the variable to.</param>
		template<typename T>
		void Set(const std::string& name, const T& value) noexcept
		{
			for (auto shader : _shaders)
			{
				shader->Set<T>(name, value);
			}
		}

		/// <summary>
		/// Sets the variable with the given name to the given value in the shader at the given index.
		/// </summary>
		/// <typeparam name="T">Type of the variable to set.</typeparam>
		/// <param name="name">Name of the variable to set.</param>
		/// <param name="value">Value to set the variable to.</param>
		/// <param name="shaderIndex">Index of the shader to set the variable in.</param>
		template<typename T>
		void Set(const std::string& name, const T& value, int shaderIndex) noexcept
		{
			_shaders[shaderIndex]->Set<T>(name, value);
		}

		/// <summary>
		/// Manually sets the data of a constant buffer in a shader.
		/// </summary>
		/// <param name="data">Data pointer</param>
		/// <param name="size">Size of the data in bytes</param>
		/// <param name="cbufferID">ID of the constant buffer</param>
		/// <param name="shaderID">ID of the shader</param>
		void SetData(void* data, size_t size, int cbufferID, int shaderID);
		void SetData(void* data, size_t size, int cbufferID);

		/// <summary>
		/// Sets the data of a constant buffer in a shader, automatically determining the size from the type T.
		/// </summary>
		/// <typeparam name="T">Type of the data to set.</typeparam>
		/// <param name="data">Pointer to the data</param>
		/// <param name="cbufferID">ID of the constant buffer</param>
		/// <param name="shaderID">ID of the shader</param>
		template<typename T>
		void SetData(T* data, int cbufferID, int shaderID)
		{
			SetData(data, sizeof(T), cbufferID, shaderID);
		}

		/// <summary>
		/// Sets the data of a constant buffer in all shaders, automatically determining the size from the type T.
		/// </summary>
		/// <typeparam name="T">Type of the data to set.</typeparam>
		/// <param name="data">Pointer to the data</param>
		/// <param name="cbufferID">ID of the constant buffer</param>
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