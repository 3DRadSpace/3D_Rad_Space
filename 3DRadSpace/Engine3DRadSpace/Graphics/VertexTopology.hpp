#pragma once

namespace Engine3DRadSpace::Graphics
{
	/// <summary>
	///	Represents veretex topology types for rendering.
	/// </summary>
	enum class VertexTopology
	{
		/// <summary>
		/// Undefined vertex topology type.
		/// </summary>
		Undefined = 0,
		/// <summary>
		/// A list of points.
		/// </summary>
		PointList,
		/// <summary>
		/// A list of lines.
		/// </summary>
		LineList,
		/// <summary>
		/// A strip of lines.
		/// </summary>
		LineStrip,
		/// <summary>
		/// A triangle list. This is the most common topology.
		/// </summary>
		TriangleList,
		/// <summary>
		/// A strip of triangles.
		/// </summary>
		TriangleStrip,
		/// <summary>
		///	A adjacency list of lines with adjacency data.
		/// </summary>
		LineList_Adj,
		/// <summary>
		///	A adjacency strip of lines with adjacency data.
		/// </summary>
		LineStrip_Adj,
		/// <summary>
		///	A adjacency list of triangles with adjacency data.
		/// </summary>
		TriangleList_Adj,
		/// <summary>
		///	A adjacency strip of triangles with adjacency data.
		/// </summary>
		TriangleStrip_Adj,
	};	 
}