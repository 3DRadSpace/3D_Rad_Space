#pragma once

namespace Engine3DRadSpace::Graphics
{
    enum class VertexTopology
    {
        Undefined = 0,
        PointList = 1,
        LineList = 2,
        LineStrip = 3,
        TriangleList = 4,
        TriangleStrip = 5,
        LineList_Adj = 10,
        LineStrip_Adj = 11,
        TriangleList_Adj = 12,
        TriangleStrip_Adj = 13,
	};	 
}