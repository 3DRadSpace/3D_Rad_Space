#pragma once
#include "Mesh.h"

#pragma warning(push)
#pragma warning(disable: 26812)
#pragma warning(disable: 26495)

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

enum class VertexDeclDeterminantFlag
{
	Null = 1 << 0,
	Position = 1 << 1,
	Normal = 1 << 2,
	TangentBitangent = 1 << 3,
	SingleUV = 1 << 4,
	MultipleUVs = 1 << 5,
	SingleVertexColor = 1 << 6,
	MultipleVertexColors = 1 << 7
};

inline VertexDeclDeterminantFlag operator |(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);
inline VertexDeclDeterminantFlag operator |=(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);
inline VertexDeclDeterminantFlag operator &(VertexDeclDeterminantFlag a, VertexDeclDeterminantFlag b);

class DLLEXPORT Model3D
{
	ID3D11Device* device;
	ID3D11DeviceContext* context;

	bool _loaded;
public:
	Model3D() :_loaded(false), Meshes(nullptr),Textures(nullptr),device(nullptr),context(nullptr) {};

	MeshPart<void>** Meshes;
	VertexDeclDeterminantFlag* MeshFlags;
	size_t NumMeshes;

	Texture2D** Textures;
	size_t NumTextures;

	
	Model3D(Game* game, const char* file);

	static bool CheckVertexDeclDeterminant(VertexDeclDeterminantFlag flag, VertexDeclDeterminantFlag comp);

	void Draw();

	~Model3D();
};

#pragma warning(pop)