#pragma once

namespace Engine3DRadSpace::Graphics
{		
	/// <summary>
	/// Represents CPU/GPU access to an GPU resource that contains an buffer.
	/// </summary>
	enum class BufferUsage : unsigned int
	{
		/// <summary>
		/// Read and write access by the GPU. Same as D3D11_USAGE_DEFAULT.
		/// </summary>
		ReadWriteGPU,
		/// <summary>
		/// Can only be read by the GPU. Same as D3D11_USAGE_IMMUTABLE.
		/// </summary>
		ReadOnlyGPU,
		/// <summary>
		/// Accessible by both the GPU (read only) and the CPU (write only). Same as D3D11_USAGE_DYNAMIC.
		/// </summary>
		ReadOnlyGPU_WriteOnlyCPU,
		/// <summary>
		/// Only supports data transfer (copy) from the GPU to the CPU.
		/// </summary>
		Staging,
	};
}