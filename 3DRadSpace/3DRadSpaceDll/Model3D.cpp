#include "Model3D.h"

inline VertexDeclDeterminantFlag operator|(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline VertexDeclDeterminantFlag operator|=(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline VertexDeclDeterminantFlag operator&(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b)
{
	return static_cast<VertexDeclDeterminantFlag>(static_cast<int>(a) & static_cast<int>(b));
}
