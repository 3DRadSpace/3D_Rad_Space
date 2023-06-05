#pragma once

namespace Engine3DRadSpace::Graphics
{
    enum class VertexTopology
    {
        Undefined = 0,
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip,
        LineList_Adj,
        LineStrip_Adj,
        TriangleList_Adj,
        TriangleStrip_Adj,
	};	 
}