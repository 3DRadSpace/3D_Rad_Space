#pragma once
#include "../Core/IService.hpp"
#include "ICamera.hpp"

namespace Engine3DRadSpace::Objects
{
	/// <summary>
	///	Stores references to all ICamera instances in the scene.
	/// </summary>
	class E3DRSP_OBJECTS_EXPORT CameraProvider : public IService
	{
		std::vector<ICamera*> _cameras;
		ICamera* _mainRTCamera = nullptr;
	public:
		/// <summary>
		///	Constructs a new instance.
		/// </summary>
		/// <param name="owner">Owner</param>
		explicit CameraProvider(IGame* owner);

		/// <summary>
		/// Returns the idx-th ICamera instance in the scene.
		/// </summary>
		/// <param name="idx">index</param>
		/// <returns>ICamera pointer.</returns>
		ICamera* operator[](size_t idx) const;

		/// <summary>
		/// Gets an reference to the active camera object.
		/// </summary>
		/// <returns>Active camera pointer.</returns>
		ICamera* GetActiveCamera() const noexcept;
		/// <summary>
		/// Same as SetActiveCamera(this->operator[](idx)), but with bounds checking.
		/// </summary>
		/// <param name="idx">index</param>
		void SetActiveCamera(size_t idx);
		/// <summary>
		/// Sets an alternate camera to be used for rendering.
		/// </summary>
		/// <param name="camera">Must be valid during draw calls</param>
		void SetActiveCamera(ICamera* camera);
		/// <summary>
		///	Should be called when adding/removing cameras into the scene.
		/// </summary>
		void Refresh();
		/// <summary>
		/// Returns the number of ICamera instances in the scene.
		/// </summary>
		/// <returns>Number of ICamera instances.</returns>
		size_t Count() const noexcept;
	};
}