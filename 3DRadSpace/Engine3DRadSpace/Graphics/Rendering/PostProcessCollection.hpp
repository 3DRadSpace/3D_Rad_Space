#pragma once
#include "PostProcessEffect.hpp"
#include "../IRenderTarget.hpp"
#include "../../Core/IService.hpp"
#include "../../Logging/Exception.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Represents multiple post processes, one applied after the other.
	/// </summary>
	class E3DRSP_GRAPHICS_RENDERING_EXPORT PostProcessCollection : public IService
	{
	private:
		IGraphicsDevice* _device;
		std::vector<std::unique_ptr<PostProcessEffect>> _effects;

		std::unique_ptr<ITexture2D> _backbuffer_cpy;
		std::unique_ptr<ITexture2D> _depthbuffer_cpy;
	public:
		/// <summary>
		/// Instantiates the list of effects.
		/// </summary>
		/// <param name="device">Graphics device.</param>
		explicit PostProcessCollection(IGraphicsDevice* device);

		PostProcessCollection(PostProcessCollection&&) noexcept = default;
		PostProcessCollection& operator=(PostProcessCollection&&) noexcept = default;

		/// <summary>
		/// Adds an effect of type E into the list. 
		/// </summary>
		/// <typeparam name="E">Must inherit PostProcessEffect</typeparam>
		/// <param name="avoid_duplicate">If there's an other instance of E, do not add a new instance.</param>
		/// <returns></returns>
		template<typename E>
		E& Add(bool avoid_duplicate = true)
		{
			if(avoid_duplicate)
			{
				auto index = Exists<E>();
				if(index.has_value())
				{
					return *dynamic_cast<E*>(_effects[index.value()].get());
				}
			}

			auto effect = std::make_unique<E>(_device);

			auto ref = static_cast<PostProcessEffect*>(effect.get());
			//ref->_output = _output.get();
			ref->_backbuffer_copy = _backbuffer_cpy.get();
			ref->_depthBuffer_copy = _depthbuffer_cpy.get();

			auto &r = _effects.emplace_back(std::move(effect));
			return *(static_cast<E*>(r.get()));
		}

		/// <summary>
		/// Returns the index-th effect.
		/// </summary>
		/// <typeparam name="E">Expected type.</typeparam>
		/// <param name="index">Array index</param>
		/// <returns>Pointer to a instance of type E.</returns>
		template<typename E>
		E* At(int index)
		{
			return dynamic_cast<E*>(_effects[index].get());
		}

		/// <summary>
		/// Checks if one or more instances of type E exist in the list.
		/// </summary>
		/// <typeparam name="E">Effect type</typeparam>
		/// <returns>Count of instances of E.</returns>
		template<typename E>
		std::optional<size_t> Exists()
		{
			for(size_t i = 0; i < _effects.size(); i++)
			{
				if(dynamic_cast<E*>(_effects[i].get()) != nullptr)
				{
					return i;
				}
			}
			return std::nullopt;
		}

		/// <summary>
		/// Gets an reference to a instance of type E. Throws a exception if E doesn't exist.
		/// </summary>
		/// <typeparam name="E">Effect type.</typeparam>
		/// <returns>Rerefence to E.</returns>
		template<typename E>
		E& Get()
		{
			auto index = Exists<E>();
			if(index.has_value())
			{
				return *dynamic_cast<E*>(_effects[index.value()].get());
			}
			else
			{
				throw Logging::Exception("Effect not found!");
			}
		}

		/// <summary>
		/// Gets a pointer to an effect of type E. If doesn't exist, nullptr is returned.
		/// </summary>
		/// <typeparam name="E">Effect type.</typeparam>
		/// <returns>Pointer to an instance of E.</returns>
		template<typename E>
		E* TryGet()
		{
			auto index = Exists<E>();
			if(index.has_value())
			{
				return dynamic_cast<E*>(_effects[index.value()].get());
			}
			else
			{
				return nullptr;
			}
		}

		/// <summary>
		/// Gets the Nth effect of type E.
		/// </summary>
		/// <typeparam name="E">Effect type</typeparam>
		/// <param name="index"></param>
		/// <returns></returns>
		template<typename E>
		E& GetNth(int index)
		{
			int count = 0;
			for(size_t i = 0; i < _effects.size(); i++)
			{
				if(dynamic_cast<E*>(_effects[i].get()) != nullptr)
				{
					if(count == index)
					{
						return *dynamic_cast<E*>(_effects[i].get());
					}
					count++;
				}
			}

			throw Logging::Exception("Effect not found!");
		}

		/// <summary>
		/// Returns the count of effects in the list, no matter their types.
		/// </summary>
		/// <returns></returns>
		size_t Length() const noexcept;

		/// <summary>
		/// Applies all effects, all after the other.
		/// </summary>
		void ApplyAll();

		/// <summary>
		/// Enables all effects.
		/// </summary>
		void EnableAll();
		/// <summary>
		/// Disables all effects.
		/// </summary>
		void DisableAll();

		~PostProcessCollection() override = default;
	};
}