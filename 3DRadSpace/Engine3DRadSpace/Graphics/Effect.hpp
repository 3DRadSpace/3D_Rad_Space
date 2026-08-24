#pragma once
#include "IGraphicsDevice.hpp"
#include "IShader.hpp"
#include "ShaderType.hpp"

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	/// Represents references to shaders, specifically vertex, pixel, and geometry shaders. This class is used to set the shaders to the graphics device.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT Effect
	{
	protected:
		IGraphicsDevice* _device;
		std::vector<IShader*> _shaders;
	public:
		/// <summary>
		/// Constructs an Effect object with the specified graphics device and shaders.
		/// </summary>
		/// <param name="device">The graphics device to be used by the effect.</param>
		/// <param name="shaders">A span of shader pointers to be used by the effect.</param>
		Effect(
			IGraphicsDevice* device, 
			std::span<IShader*> shaders
		);

		Effect(const Effect &p) = delete;
		/// <summary>
		/// Move constructor for the Effect class. Transfers ownership of resources from another Effect object to this one.
		/// </summary>
		/// <param name="p">The Effect object to move from.</param>
		Effect(Effect&& p) noexcept = default;

		Effect &operator =(const Effect &p) = delete;
		/// <summary>
		/// Move assignment operator for the Effect class. Transfers ownership of resources from another Effect object to this one.
		/// </summary>
		/// <param name="p">The Effect object to move from.</param>
		/// <returns>The current Effect object with resources transferred from the other Effect object.</returns>
		Effect& operator =(Effect&& p) noexcept = default;
		
		/// <summary>
		/// Sets all the effects.
		/// </summary>
		/// <returns>Number of effects succesfully set.</returns>
		int SetAll() const noexcept;

		/// <summary>
		/// Sets the index-th shader.
		/// </summary>
		/// <param name="index">The index of the shader to set.</param>
		/// <returns>True if the shader was successfully set; otherwise, false.</returns>
		bool Set(int index) const noexcept;
	
		/// <summary>
		/// Sets the value of variable named "name" in all shaders that are owned by this instance.
		/// </summary>
		/// <typeparam name="T">The type of the value to set.</typeparam>
		/// <param name="name">The name of the variable to set.</param>
		/// <param name="value">The value to set.</param>
		template<typename T>
		void Set(const std::string& name, const T& value) noexcept
		{
			for (auto shader : _shaders)
			{
				shader->Set<T>(name, value);
			}
		}

		/// <summary>
		///	Sets the value of variable named "name" in the specified shader.
		/// </summary>
		/// <typeparam name="T">The type of the value to set.</typeparam>
		/// <param name="name">The name of the variable to set.</param>
		/// <param name="value">The value to set.</param>
		/// <param name="shaderIndex">The index of the shader in which to set the variable.</param>
		template<typename T>
		void Set(const std::string& name, const T& value, int shaderIndex) noexcept
		{
			_shaders[shaderIndex]->Set<T>(name, value);
		}

		/// <summary>
		/// Directly sets the data of a constant buffer in an specified shader.
		/// </summary>
		/// <param name="data">Pointer to the new constant buffer data.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <param name="cbufferID">The ID of the constant buffer to set.</param>
		/// <param name="shaderID">The ID of the shader in which to set the constant buffer.</param>
		void SetData(void* data, size_t size, int cbufferID, int shaderID);
		/// <summary>
		/// Directly sets the data of a constant buffer in all shaders owned by this instance.
		/// </summary>
		/// <param name="data">Pointer to the new constant buffer data.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <param name="cbufferID">The ID of the constant buffer to set.</param>
		void SetData(void* data, size_t size, int cbufferID);

		/// <summary>
		/// Directly sets the data of a constant buffer in an specified shader, using a templated type to determine the size of the data.
		/// </summary>
		/// <remarks>
		/// T must have an alignment of 16 bytes (alignas(16)) to ensure proper alignment for GPU constant buffers.
		/// </remarks>
		/// <typeparam name="T">The type of the data to set.</typeparam>
		/// <param name="data">Pointer to the new constant buffer data.</param>
		/// <param name="cbufferID">The ID of the constant buffer to set.</param>
		/// <param name="shaderID">The ID of the shader in which to set the constant buffer.</param>
		template<typename T>
		void SetData(T* data, int cbufferID, int shaderID)
		{
			SetData(data, sizeof(T), cbufferID, shaderID);
		}
		
		/// <summary>
		/// Directly sets the data of a constant buffer in all shaders owned by this instance, using a templated type to determine the size of the data.
		/// </summary>
		/// <remarks>
		/// T must have an alignment of 16 bytes (alignas(16)) to ensure proper alignment for GPU constant buffers.
		/// </remarks>
		/// <typeparam name="T">The type of the data to set.</typeparam>
		/// <param name="data">Pointer to the new constant buffer data.</param>
		/// <param name="cbufferID">The ID of the constant buffer to set.</param>
		template<typename T>
		void SetData(T* data, int cbufferID)
		{
			SetData(static_cast<void*>(data), sizeof(T), cbufferID);
		}

		/// <summary>
		/// Sets a texture to all shaders owned by this instance at the specified index.
		/// </summary>
		/// <param name="texture">Texture to set.</param>
		/// <param name="idx">The index at which to set the texture.</param>
		void SetTexture(ITexture2D* texture, int idx) noexcept;
		/// <summary>
		/// Sets a texture to a specific shader owned by this instance at the specified index.
		/// </summary>
		/// <param name="texture">Texture to set.</param>
		/// <param name="textureID">The index at which to set the texture.</param>
		/// <param name="shaderID">The ID of the shader in which to set the texture.</param>
		void SetTexture(ITexture2D* texture, int textureID, int shaderID) noexcept;
		/// <summary>
		/// Sets a sampler state to all shaders owned by this instance at the specified index.
		/// </summary>
		/// <param name="sampler">The sampler state to set.</param>
		/// <param name="idx">The index at which to set the sampler state.</param>
		void SetSampler(ISamplerState* sampler, int idx) noexcept;
		/// <summary>
		/// Sets a sampler state to a specific shader owned by this instance at the specified index.
		/// </summary>
		/// <param name="sampler">The sampler state to set.</param>
		/// <param name="samplerID">The index at which to set the sampler state.</param>
		/// <param name="shaderID">The ID of the shader in which to set the sampler state.</param>
		void SetSampler(ISamplerState* sampler, int samplerID, int shaderID) noexcept;

		/// <summary>
		/// Gets the shader at the specified index.
		/// </summary>
		/// <param name="idx">The index of the shader to retrieve.</param>
		IShader* operator[](size_t idx) const;

		~Effect() = default;
	};
}