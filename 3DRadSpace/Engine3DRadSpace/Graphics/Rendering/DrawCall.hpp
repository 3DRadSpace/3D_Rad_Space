#pragma once
#include "RenderPassType.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../VertexTopology.hpp"

namespace Engine3DRadSpace::Graphics
{
	class ModelMeshPart;

	namespace Rendering
	{
		/// <summary>
		/// Represents a single draw call for a mesh part.
		/// </summary>
		struct DrawCall
		{
			ModelMeshPart* MeshPart = nullptr;

			Math::Matrix4x4 View;
			Math::Matrix4x4 Projection;

			/// <summary>
			/// World matrices for all instances.
			/// </summary>
			std::vector<Math::Matrix4x4> InstanceWorlds;
			/// <summary>
			/// Additional instance data for this draw call. Constant buffer arrays for each instance.
			/// </summary>
			/// <remarks>
			/// 
			/// </remarks>
			std::vector<std::unique_ptr<std::byte[]>> InstanceData;
			RenderPassType PassType = RenderPassType::Hidden;
			bool IsInstanced = false;
			VertexTopology Topology = VertexTopology::TriangleList;

			DrawCall() = default;
			DrawCall(DrawCall&&) noexcept = default;
			DrawCall& operator=(DrawCall&&) noexcept = default;

			DrawCall(const DrawCall&) = delete;
			DrawCall& operator=(const DrawCall&) = delete;
		};
	}
}