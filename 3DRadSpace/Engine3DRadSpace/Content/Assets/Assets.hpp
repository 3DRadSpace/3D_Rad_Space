#pragma once
#include "../ContentManager.hpp"

/*
	This header is not supposed to be included by the user as it is used internally when initializing content related services.
*/

namespace Engine3DRadSpace::Internal
{
	/// <summary>
	/// Registers the default asset types with the content manager.
	/// </summary>
	/// <param name="manager">Pointer to the content manager.</param>
	void E3DRSP_CONTENT_ASSETS_EXPORT RegisterDefaultTypes(Content::ContentManager* manager);
}