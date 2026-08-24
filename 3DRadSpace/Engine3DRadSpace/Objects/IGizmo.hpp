#pragma once
#include "IObject.hpp"
#include "../Core/IDrawable2D.hpp"
#include "../Core/IDrawable3D.hpp"

namespace Engine3DRadSpace::Objects::Gizmos
{
	/// <summary>
	/// Base type for all gizmos.
	/// </summary>
	class E3DRSP_OBJECTS_GIZMOS_EXPORT IGizmo: public IUpdateable, public IDrawable3D, public IDrawable2D, public ILoadable
	{
	protected:
		/// <summary>
		/// Default constructor for IGizmo.
		/// </summary>
		IGizmo() = default;
		/// <summary>
		/// Complete constructor for IGizmo.
		/// </summary>
		/// <param name="allow3DRendering">Is 3D rendering allowed.</param>
		/// <param name="allow2DRendering">Is 2D rendering allowed.</param>
		/// <param name="allowUpdating">Is updating allowed.</param>
		/// <param name="allowTranslating">Is translating allowed.</param>
		/// <param name="allowRotating">Is rotating allowed.</param>
		/// <param name="allowScaling">Is scaling allowed.</param>
		IGizmo(
			bool allow3DRendering,
			bool allow2DRendering,
			bool allowUpdating,
			bool allowTranslating,
			bool allowRotating,
			bool allowScaling
		);

		IGizmo(const IGizmo&) = default;
		IGizmo& operator=(const IGizmo&) = default;

		IGizmo(IGizmo&&) noexcept = default;
		IGizmo& operator=(IGizmo&&) noexcept = default;
	public:
		/// <summary>
		/// The object that's currently selected.
		/// </summary>
		IObject* Object = nullptr;
		/// <summary>
		/// Is the object selected?
		/// </summary>
		bool Selected = false;
		///<summary>
		/// Does the gizmo support 3d rendering?
		/// </summary>
		bool Allow3DRendering = true;
		/// <summary>
		/// Does the gizmo support 2d rendering?
		/// </summary>
		bool Allow2DRendering = false;
		/// <summary>
		/// Does the gizmo support updating?
		/// </summary>
		bool AllowUpdating = false;

		/// <summary>
		/// Does the gizmo support translating?
		/// </summary>
		bool AllowTranslating = true;
		/// <summary>
		/// Does the gizmo support rotating?
		/// </summary>
		bool AllowRotating = true;
		/// <summary>
		/// Does the gizmo support scaling?
		/// </summary>
		bool AllowScaling = true;

		virtual ~IGizmo() = default;
	};
}