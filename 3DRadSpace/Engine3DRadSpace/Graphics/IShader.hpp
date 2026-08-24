#pragma once
#include "ShaderFeatureLevel.hpp"
#include "IGPUResource.hpp"

namespace Engine3DRadSpace::Reflection
{
	class IReflectedField;
}

namespace Engine3DRadSpace::Graphics
{
	class ITexture1D;
	class ITexture2D;
	class ITextureCube;
	class ISamplerState;

	/// <summary>
	/// Represents a shader program that can be used in the rendering pipeline.
	/// </summary>
	class E3DRSP_GRAPHICS_EXPORT IShader : public IGPUResource
	{
	protected:
		IShader() = default;

		IShader(const IShader&) = delete;
		IShader(IShader&&) noexcept = default;

		IShader& operator=(const IShader&) = delete;
		IShader& operator=(IShader&&) noexcept = default;
	public:
		///<summary>
		/// Sets an entire uniform buffer to the shader.
		/// </summary>
		virtual void SetData(unsigned index, const void *data, size_t dataSize) = 0;

		/// <summary>
		/// Sets the specified texture to a given index.
		/// </summary>
		/// <param name="index">The index at which to set the texture.</param>
		/// <param name="texture">The texture to set.</param>
		virtual void SetTexture(unsigned index, ITexture1D* texture) = 0;
		/// <summary>
		///	Sets multiple textures to the shader using a span of ITexture1D pointers.
		/// </summary>
		/// <param name="textures">A span of ITexture1D pointers to set.</param>
		virtual void SetTextures(std::span<ITexture1D*> textures) = 0;

		/// <summary>
		/// Sets an 2D texture to the shader at the specified index.
		/// </summary>
		/// <param name="index">The index at which to set the texture.</param>
		/// <param name="texture">The texture to set.</param>
		virtual void SetTexture(unsigned index, ITexture2D *texture) = 0;
		/// <summary>
		/// Sets multiple 2D textures to the shader using a span of ITexture2D pointers.
		/// </summary>
		/// <param name="textures">A span of ITexture2D pointers to set.</param>
		virtual void SetTextures(std::span<ITexture2D*> textures) = 0;
		/// <summary>
		/// Sets an cube texture to the shader at the specified index.
		/// </summary>
		/// <param name="index">The index at which to set the texture.</param>
		/// <param name="texture">The texture to set.</param>
		virtual void SetTexture(unsigned index, ITextureCube *texture) = 0;
		/// <summary>
		/// Sets multiple cube textures to the shader using a span of ITextureCube pointers.
		/// </summary>
		/// <param name="textures">A span of ITextureCube pointers to set.</param>
		virtual void SetTextures(std::span<ITextureCube*> textures) = 0;
		/// <summary>
		///	Sets an texture sampler state at the specified index.
		/// </summary>
		/// <param name="index">The index at which to set the sampler state.</param>
		/// <param name="samplerState">The sampler state to set.</param>
		virtual void SetSampler(unsigned index, ISamplerState *samplerState) = 0;
		/// <summary>
		///	Sets the constant buffers and the shader to the rendering pipeline.
		/// </summary>
		virtual void SetShader() = 0;

		/// <summary>
		/// Gets the exposed variables of the shader, which can be used to set values for the shader's uniform buffers.
		/// </summary>
		/// <returns>Shader reflection data for variables in constant buffers.</returns>
		virtual std::vector<Reflection::IReflectedField*> GetVariables() const = 0;
		/// <summary>
		///	Sets a value for a shader variable by name. The data is copied into the shader's uniform buffer.
		/// </summary>
		/// <remarks>
		/// Prefer setting the data drectly using the SetData<T> method for better performance.
		/// </remarks>
		/// <param name="name">The name of the shader variable to set.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="dataSize">The size of the data in bytes.</param>
		virtual void Set(const std::string& name, const void* data, size_t dataSize) = 0;

		/// <summary>
		///	Sets a value for a shader variable by name. The data is copied into the shader's uniform buffer.
		/// </summary>
		/// <typeparam name="T">The type of the data to set.</typeparam>
		/// <param name="name">The name of the shader variable to set.</param>
		/// <param name="data">The data to set.</param>
		template<typename T>
		void Set(const std::string& name, const T& data)
		{
			Set(name, &data, sizeof(T));
		}

		/// <summary>
		/// Sets an entire uniform buffer to the shader.
		/// </summary>
		/// <typeparam name="T">The type of the data to set.</typeparam>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="index">The index of the uniform buffer to set.</param>	
		template<typename T>
		void SetData(const T* data, unsigned index)
		{
			SetData(index, data, sizeof(T));
		}

		/// <summary>
		/// Gets the name of the entry point function for this shader.
		/// </summary>
		/// <returns>The name of the entry point function</returns>
		virtual std::string_view GetEntryName() const noexcept = 0;
		/// <summary>
		/// Gets the compilation results for this shader.
		/// </summary>
		/// <returns>A string containing any compilation errors or warnings, or an empty string if the shader compiled successfully.</returns>
		virtual const char* GetCompilationErrorsAndWarnings() const noexcept = 0;

		~IShader() override = default;
	};
}