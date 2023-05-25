#pragma once

namespace Engine3DRadSpace
{
	class IInitiializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitiializable() = default;
	};
}