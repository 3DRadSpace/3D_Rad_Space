#pragma once
#include "IObject.hpp"
#include "../Core/IDrawable2D.hpp"
#include "../Core/IDrawable3D.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	class E3DRSP_OBJECTS_GIZMOS_EXPORT IGizmo: public IUpdateable, public IDrawable3D, public IDrawable2D, public ILoadable
	{
	protected:
		IGizmo() = default;

		IGizmo(const IGizmo&) = default;
		IGizmo& operator=(const IGizmo&) = default;

		IGizmo(IGizmo&&) noexcept = default;
		IGizmo& operator=(IGizmo&&) noexcept = default;
	public:
		/// <summary>
		/// The object that's currently selected.
		/// </summary>
		IObject* Object = nullptr;

		bool Selected = false;

		bool Allow3DRendering = true;
		bool Allow2DRendering = true;
		bool AllowUpdating = false;

		bool AllowTranslating = true;
		bool AllowRotating = true;
		bool AllowScaling = true;

		virtual ~IGizmo() = default;
	};
}