#pragma once
#include "RenderPassType.hpp"
#include "../ModelMeshPart.hpp"

namespace Engine3DRadSpace::Graphics::Rendering
{
	/// <summary>
	/// Contains information about a mesh part to be drawn, including material info, and transformation matrices.
	/// </summary>
	struct MeshPartDrawInfo
	{
		ModelMeshPart* Part;
		RenderPassType PassType;
		Math::Matrix4x4 World;
		Math::Matrix4x4 View;
		Math::Matrix4x4 Projection;
	};
}