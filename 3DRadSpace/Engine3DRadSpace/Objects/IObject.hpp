#pragma once
#include "../Math\Matrix4x4.hpp"
#include "../Core/IInitializable.hpp"
#include "../Core/IUpdateable.hpp"
#include "../Core/ILoadable.hpp"
#include "../Reflection/UUID.hpp"
#include "../Core/IService.hpp"
#include "ObjectCollection.hpp"

namespace Engine3DRadSpace
{
	class IGame;
	class Game;

	namespace Objects::Gizmos
	{
		class IGizmo;
	}

	namespace Graphics
	{
		class IGraphicsDevice;
	}

	namespace Objects
	{
		class ObjectList;

		class E3DRSP_OBJECTS_EXPORT IObject : public IInitializable, public IUpdateable, public ILoadable
		{
		protected:
			IGame* _game = nullptr;
			Graphics::IGraphicsDevice* _device = nullptr;

			IObject* _parent = nullptr;
			/// <summary>
			/// Default constructor used for reflection. Objects created with this constructor are initially invalid, until internalInitialize() is called.
			/// </summary>
			/// <param name="name"></param>
			/// <param name="tag"></param>
			/// <param name="enabled"></param>
			/// <param name="visible"></param>
			explicit IObject(const std::string& name = "Empty", bool enabled = false, bool visible = false);

			IObject(const IObject&) noexcept = delete;
			IObject& operator=(const IObject&) noexcept = delete;

			IObject(IObject&&) noexcept = default;
			IObject& operator=(IObject&&) noexcept = default;
		public:
			std::string Name;
			bool Enabled;
			bool Visible;

			ChildObjectCollection Children;

			/// <summary>
			/// Called by ObjectsList to set the _game Game instance. If there are objects manually managed, this MUST be called before Initialize or EditorInitialize.
			/// </summary>
			/// <param name="game">Application context</param>
			void InternalInitialize(IGame* game);

			virtual Reflection::UUID GetUUID() const noexcept = 0;
			virtual Objects::Gizmos::IGizmo* GetGizmo() const noexcept = 0;

			Graphics::IGraphicsDevice* GetGraphicsDeviceHandle() const noexcept;
			IGame* GetGame() const noexcept;

			IObject* operator[](size_t idxChild) const;
			IObject* GetParent() const noexcept;
			void SetParent(IObject* newParent) noexcept;

			bool HasParent() const noexcept;
			size_t GetChildrenCount() const noexcept;

			///Getters and setters for events and visual scripting

			virtual void Enable();
			virtual void Disable();
			virtual bool Switch();

			virtual void Show();
			virtual void Hide();
			virtual bool SwitchVisibility();

			virtual ~IObject();

			friend class Game;
			friend class ObjectList;
		};
	}
}


