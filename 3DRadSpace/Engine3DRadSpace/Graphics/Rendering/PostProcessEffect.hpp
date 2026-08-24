#pragma once
#include "../IShader.hpp"
#include "../ShaderDesc.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents a pixel shader that is applied to the backbuffer.
	/// </summary>
	/// <remarks>
	/// By default, copies of the back buffer and depth buffer are sent as textures to the specified Fragment/Pixel shader. Use <c>NotDepthAware = true</c> to only upload the backbuffer.
	/// </remarks>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT PostProcessEffect : public IShader
	{
	private:
		IShader* _vertex;
		IShader* _effect;

		ITexture2D* _backbuffer_copy;
		ITexture2D* _depthBuffer_copy;
	protected:
		IGraphicsDevice* _device;
	public:
		/// <summary>
		///	Creates a new post process effect with the given shader description.
		/// </summary>
		/// <param name="device">The graphics device.</param>
		/// <param name="effect">The shader description.</param>
		PostProcessEffect(IGraphicsDevice* device, ShaderDesc& effect);
		/// <summary>
		/// Is this effect enabled?
		/// </summary>
		bool Enabled = true;

		bool NotDepthAware = false;

		/// <summary>
		/// Applies the effect.
		/// </summary>
		virtual void Apply();
		/// <summary>
		/// Draws a screen quad containing the processed texture, usually the backbuffer.
		/// </summary>
		void Draw();

		/// <summary>
		/// Sets a texture to the shader at the specified index.
		/// </summary>
		/// <param name="index">The index of the texture slot.</param>
		/// <param name="texture">The texture to set.</param>
		void SetTexture(unsigned index, ITexture1D* texture) override;
		/// <summary>
		/// Sets multiple textures to the shader using a span of ITexture1D pointers.
		/// </summary>
		/// <param name="textures">A span of ITexture1D pointers to set.</param>
		void SetTextures(std::span<ITexture1D*> textures) override;
		/// <summary>
		/// Sets a 2D texture to the shader at the specified index.
		/// </summary>
		/// <param name="index">The index of the texture slot.</param>
		/// <param name="texture">The texture to set.</param>
		void SetTexture(unsigned index, ITexture2D* texture) override;
		/// <summary>
		/// Sets multiple 2D textures to the shader using a span of ITexture2D pointers.
		/// </summary>
		/// <param name="textures">A span of ITexture2D pointers to set.</param>
		void SetTextures(std::span<ITexture2D*> textures) override;

		/// <summary>
		/// Sets a cubemap texture to the shader at the specified index.
		/// </summary>
		/// <param name="index">The index of the texture slot.</param>
		/// <param name="texture">The cubemap texture to set.</param>
		void SetTexture(unsigned index, ITextureCube* texture) override;
		/// <summary>
		/// Sets multiple cubemap textures to the shader using a span of ITextureCube pointers.
		/// </summary>
		/// <param name="textures">A span of ITextureCube pointers to set.</param>
		void SetTextures(std::span<ITextureCube*> textures) override;
		/// <summary>
		///	Sets the given sampler state at the specified index.
		/// </summary>
		/// <param name="index">The index of the sampler slot.</param>
		/// <param name="sampler">The sampler state to set.</param>
		void SetSampler(unsigned index, ISamplerState* sampler) override;
		/// <summary>
		/// Sets the given data for the specified constant buffer.
		/// </summary>
		/// <param name="index">The index of the constant buffer slot.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="size">The size of the data in bytes.</param>
		void SetData(unsigned index, const void* data, size_t size) override;
		/// <summary>
		/// Sets the shader to the rendering pipeline.
		/// </summary>
		void SetShader() override;

		/// <summary>
		/// Gets the reflection data for all variables in the shader's constant buffers, which can be used to set values for the shader's uniform buffers.
		/// </summary>
		/// <returns>A vector of pointers to reflected fields.</returns>
		std::vector<Reflection::IReflectedField*> GetVariables() const override;
		/// <summary>
		/// Sets the value of a shader variable by name.
		/// </summary>
		/// <param name="name">The name of the shader variable.</param>
		/// <param name="data">A pointer to the data to set.</param>
		/// <param name="dataSize">The size of the data in bytes.</param>
		void Set(const std::string& name, const void* data, size_t dataSize) override;
		/// <summary>
		/// Gets the name of the entry point function for the shader.
		/// </summary>
		/// <returns>The name of the entry point function.</returns>
		std::string_view GetEntryName() const noexcept override;
		/// <summary>
		/// Gets the compilation log containing errors and warnings.
		/// </summary>
		/// <returns>A C-style string containing the compilation log.</returns>
		const char* GetCompilationErrorsAndWarnings() const noexcept override;
		/// <summary>
		/// Gets an handle to the vertex shader.
		/// </summary>
		void* GetHandle() const noexcept override;
		/// <summary>
		/// Returns the graphics device that created this instance.
		/// </summary>
		/// <returns>Graphics device instance</returns>
		IGraphicsDevice* GetGraphicsDevice() const noexcept override;

		~PostProcessEffect() override = default;

		friend class PostProcessCollection;
	};
}