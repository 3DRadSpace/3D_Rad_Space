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

		virtual void SetTexture(unsigned index, ITexture1D* texture) = 0;
		virtual void SetTextures(std::span<ITexture1D*> textures) = 0;

		virtual void SetTexture(unsigned index, ITexture2D *texture) = 0;
		virtual void SetTextures(std::span<ITexture2D*> textures) = 0;

		virtual void SetTexture(unsigned index, ITextureCube *texture) = 0;
		virtual void SetTextures(std::span<ITextureCube*> textures) = 0;

		virtual void SetSampler(unsigned index, ISamplerState *samplerState) = 0;
		virtual void SetShader() = 0;

		virtual std::vector<Reflection::IReflectedField*> GetVariables() const = 0;
		virtual void Set(const std::string& name, const void* data, size_t dataSize) = 0;

		template<typename T>
		void Set(const std::string& name, const T& data)
		{
			Set(name, &data, sizeof(T));
		}

		virtual std::string_view GetEntryName() const noexcept = 0;
		virtual const char* GetCompilationErrorsAndWarnings() const noexcept = 0;

		~IShader() override = default;
	};
}