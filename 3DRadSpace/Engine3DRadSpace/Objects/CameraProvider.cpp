#include "CameraProvider.hpp"
#include "ObjectList.hpp"
#include "../Logging/Exception.hpp"

using namespace Engine3DRadSpace;
using namespace Engine3DRadSpace::Objects;

CameraProvider::CameraProvider(IGame* owner) : IService(owner)
{
	Refresh();
}

void CameraProvider::Refresh()
{
	_cameras.clear();

	auto objList = _owner->RequireService<ObjectList>({});
	if (objList == nullptr) throw Logging::Exception("CameraProvider requires ObjectList service to be available.");

	size_t numCameras = 0;
	for (auto& obj : *objList)
	{
		if (ICamera* cam = dynamic_cast<ICamera*>(obj.Object.get()))
		{
			_cameras.push_back(cam);

			if (numCameras == 0)
			{
				_mainRTCamera = cam;
			}

			++numCameras;
		}
	}
}

void CameraProvider::SetActiveCamera(size_t idx)
{
	if (idx >= _cameras.size())
		throw Logging::Exception("CameraProvider: Index out of range.");
	_mainRTCamera = _cameras[idx];
}

void CameraProvider::SetActiveCamera(ICamera* camera)
{
	_mainRTCamera = camera;
}

ICamera* CameraProvider::GetActiveCamera() const noexcept
{
	return _mainRTCamera;
}

ICamera* CameraProvider::operator[](size_t idx) const
{
	if (idx >= _cameras.size())
		throw Logging::Exception("CameraProvider: Index out of range.");
	return _cameras[idx];
}

size_t CameraProvider::Count() const noexcept
{
	return _cameras.size();
}

