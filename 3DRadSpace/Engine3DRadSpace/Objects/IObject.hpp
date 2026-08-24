#pragma once
#include "../Math\Matrix4x4.hpp"
#include "../Core/IInitializable.hpp"
#include "../Core/IUpdateable.hpp"
#include "../Core/ILoadable.hpp"
#include "../Reflection/UUID.hpp"
#include "../Core/IService.hpp"
#include "ChildObjectCollection.hpp"

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

		/// <summary>
		/// Base polymorphic type of all objects that can be contained in a scene/ObjectList.
		/// </summary>
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
			/// <summary>
			/// Name of the object.
			/// </summary>
			std::string Name;
			/// <summary>
			/// Is this object enabled?
			/// </summary>
			bool Enabled;
			/// <summary>
			/// Is this object visible?
			/// </summary>
			bool Visible;
			/// <summary>
			/// Children of this object.
			/// </summary>
			ChildObjectCollection Children;

			/// <summary>
			/// Called by ObjectsList to set the _game Game instance. If there are objects manually managed, this MUST be called before Initialize or EditorInitialize.
			/// </summary>
			/// <param name="game">Application context</param>
			void InternalInitialize(IGame* game);
			/// <summary>
			/// Returns the unique identifier of this object. This is used for serialization and deserialization.
			/// </summary>
			/// <returns>The unique identifier of this object.</returns>
			virtual Reflection::UUID GetUUID() const noexcept = 0;
			/// <summary>
			/// Returns the gizmo object of this object, used for editor/debug rendering.
			/// </summary>
			/// <returns>Pointer to a gizmo instance. Null if no gizmo is associated with this object.</returns>
			virtual Objects::Gizmos::IGizmo* GetGizmo() const noexcept = 0;
			/// <summary>
			/// Returns the graphics device handle associated with this object.
			/// </summary>
			/// <returns>Pointer to the graphics device handle.</returns>
			Graphics::IGraphicsDevice* GetGraphicsDeviceHandle() const noexcept;
			/// <summary>
			///	Gets the game that this object belongs to.
			/// </summary>
			/// <returns></returns>
			IGame* GetGame() const noexcept;
			/// <summary>
			/// Returns the idx-th child of this object.
			/// </summary>
			/// <param name="idxChild">Child index</param>
			/// <returns>Pointer to the idx-th child object.</returns>
			IObject* operator[](size_t idxChild) const;
			/// <summary>
			/// Returns the parent of this object.
			/// </summary>
			/// <returns>Pointer to the parent object.</returns>
			IObject* GetParent() const noexcept;
			/// <summary>
			/// Sets the parent of this object.
			/// </summary>
			/// <param name="newParent">Pointer to the new parent object.</param>
			void SetParent(IObject* newParent) noexcept;

			/// <summary>
			/// Checks if this object has a parent.
			/// </summary>
			/// <returns>True if this object has a parent, false otherwise.</returns>
			bool HasParent() const noexcept;
			/// <summary>
			/// Returns the number of children of this object.
			/// </summary>
			/// <returns>The number of children.</returns>
			size_t GetChildrenCount() const noexcept;

			/// <summary>
			/// Enables this object.
			/// </summary>
			virtual void Enable();
			/// <summary>
			///	Disables this object.
			/// </summary>
			virtual void Disable();
			/// <summary>
			/// Switched the enable/disable state of this object.
			/// </summary>
			/// <returns>The new state.</returns>
			virtual bool Switch();
			
			/// <summary>
			/// Shows this object.
			/// </summary>
			virtual void Show();
			/// <summary>
			/// Hides this object.
			/// </summary>
			virtual void Hide();
			/// <summary>
			/// Switches the visibility state of this object.
			/// </summary>
			/// <returns>The new visibility state.</returns>
			virtual bool SwitchVisibility();

			virtual ~IObject();

			friend class Game;
			friend class ObjectList;
		};
	}
}


