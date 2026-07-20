#pragma once
#include "../Reflection/ReflectedObject.hpp"
#include "../FFI/Core/RawSpan.h"

namespace Engine3DRadSpace
{
	namespace Plugins
	{
		/// <summary>
		/// Returns a span of ReflectedObject references that contain custom object reflection data.
		/// </summary>
		typedef E3DRSP_RawSpan(*LoadCustomObjects)(void);

		/// <summary>
		/// Loads custom objects from a library handle for the editor.
		/// </summary>
		/// <returns>The number of custom objects loaded.</returns>
		/// <param name="libraryHandle">HMODULE in Windows, void* in Linux</param>
		size_t E3DRSP_PLUGINS_EXPORT LoadCustomObjectsFromLibHandle(void* libraryHandle);

		/// <summary>
		/// The function signature for the function that creates a custom window for editing a custom object in the editor.
		/// </summary>
		/// <remarks>
		/// Returns a pointer to the new or updated object.
		/// 
		/// The arguments are:
		/// - HWND : Window Handle
		/// - HINSTANCE : Instance Handle
		/// - Engine3DRadSpace::Reflection::ReflectedObject* : Reflection data for the object
		/// - Engine3DRadSpace::Content::ContentManager* : Content manager for the object
		/// - Engine3DRadSpace::Objects::IObject* : The object being edited, can be nullptr if the object is being created for the first time
		/// 
		/// An analogue for the default implementation would be EditObjectDialog(...).ShowDialog().
		/// </remarks>
		typedef void*(*ObjectCustomWindow)(
			void* hwnd,
			void* hInstance,
			void* reflectionData,
			void* contentManager,
			void* object
		);
	}
}