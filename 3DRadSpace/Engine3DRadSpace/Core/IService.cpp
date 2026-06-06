#include "IService.hpp"
#include "IGame.hpp"

using namespace Engine3DRadSpace;

IService::IService() : _owner(nullptr)
{
}

IService::IService(IGame* owner) : _owner(owner)
{
}

IGame* IService::GetOwner() const noexcept
{
	return _owner;
}
