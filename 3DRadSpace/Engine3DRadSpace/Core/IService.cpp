#include "IService.hpp"
#include "IGame.hpp"

using namespace Engine3DRadSpace;

void IService::SetOwner(IGame* owner) noexcept
{
	_owner = owner;
}

IGame* IService::GetOwner() const noexcept
{
	return _owner;
}
