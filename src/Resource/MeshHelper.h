//#include <fbxsdk.h>
#include <DirectXMath.h>
#include <vector>
#include <Utility/DebugHelper.h>
#include <assimp/Importer.hpp>
using namespace DirectX;

struct m_Vertex
{
    XMFLOAT3 position;   // Vertex positions
    XMFLOAT3 normal;    // Vertex normals
    XMFLOAT2 uv;          // Vertex UVs
    int index; // Control Point Index
};
struct m_Mesh
{
    std::vector<m_Vertex> vertices;
	std::vector<unsigned int> indices;
};

