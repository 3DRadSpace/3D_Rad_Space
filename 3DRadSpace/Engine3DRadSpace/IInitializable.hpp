#pragma once

namespace Engine3DRadSpace
{
	class DLLEXPORT IInitiializable
	{
	public:
		virtual void Initialize() = 0;
		inline virtual ~IInitiializable() = default;
	};
}