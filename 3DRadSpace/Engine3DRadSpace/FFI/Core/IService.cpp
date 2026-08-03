#include "../../Core/IService.hpp"
#include "IService.h"

using namespace Engine3DRadSpace;

E3DRSP_IGame E3DRSP_IService_GetOwner(E3DRSP_IService service)
{
	if (service == nullptr) return nullptr;
	return static_cast<E3DRSP_IGame>(reinterpret_cast<IService*>(service)->GetOwner());
}

void E3DRSP_IService_Destroy(E3DRSP_IService* service)
{
	if(service != nullptr)
		delete reinterpret_cast<IService*>(service);
}