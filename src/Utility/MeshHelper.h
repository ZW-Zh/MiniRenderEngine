#include <DirectXMath.h>
#include <vector>
#include <Utility/DebugHelper.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

static void processNode(aiNode *node, const aiScene *scene,m_Mesh& m_mesh)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            m_Vertex vertex;
            //position
            vertex.position.x = mesh->mVertices[i].x;
            vertex.position.y = mesh->mVertices[i].y;
            vertex.position.z = mesh->mVertices[i].z; 
            //normal
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
            //uv
            if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
            {
                vertex.uv.x = mesh->mTextureCoords[0][i].x; 
                vertex.uv.y = mesh->mTextureCoords[0][i].y;                
            }
            else
                vertex.uv = XMFLOAT2(0.0f, 0.0f);   
            
            m_mesh.vertices.push_back(vertex);
        }
        //indices
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                m_mesh.indices.push_back(face.mIndices[j]);
        }
        //texture,能找到贴图名字
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, m_mesh);
    }
}
static void loadModel(std::string fileName, m_Mesh& mesh)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);//处理为全三角形和翻转y轴坐标
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        OutputDebugPrintf("ERROR::ASSIMP::%s", importer.GetErrorString());
        return;
    }
    

    processNode(scene->mRootNode, scene, mesh);
}
