#include <fbxsdk.h>
#include <DirectXMath.h>
#include <vector>
#include <Utility/DebugHelper.h>
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

inline void ProcessMesh(FbxMesh* pMesh, m_Mesh& mesh)
{

    int polygonCount = pMesh->GetPolygonCount();
    FbxVector4* controlPoints = pMesh->GetControlPoints();
    int controlPointCount = pMesh->GetControlPointsCount();
    int vertexID = 0;
    OutputDebugPrintf("%d",controlPointCount);
    for (int polygon = 0; polygon < polygonCount; polygon++)//遍历所有的面
    {
        int polyVertCount = pMesh->GetPolygonSize(polygon);

        for (int polyVert = 0; polyVert < polyVertCount; polyVert++)
        {
            
            m_Vertex v;
            int cpIndex = pMesh->GetPolygonVertex(polygon, polyVert);
            v.index = cpIndex;
            v.position = XMFLOAT3((float)controlPoints[cpIndex].mData[0],
                (float)controlPoints[cpIndex].mData[1],
                (float)controlPoints[cpIndex].mData[2]);
            int uvElementCount = pMesh->GetElementUVCount();

            for (int uvElement = 0; uvElement < uvElementCount; uvElement++)
            {
                FbxGeometryElementUV* geomElementUV = pMesh -> GetElementUV(uvElement);

                FbxLayerElement::EMappingMode mapMode = geomElementUV->GetMappingMode();
                FbxLayerElement::EReferenceMode refMode = geomElementUV->GetReferenceMode();

                int directIndex = -1;

                if (FbxGeometryElement::eByControlPoint == mapMode)
                {
                    if (FbxGeometryElement::eDirect == refMode)
                    {
                        directIndex = cpIndex;
                    }
                    else if (FbxGeometryElement::eIndexToDirect == refMode)
                    {
                        directIndex = geomElementUV->GetIndexArray().GetAt(cpIndex);
                    }
                }
                else if (FbxGeometryElement::eByPolygonVertex == mapMode)
                {
                    if (FbxGeometryElement::eDirect == refMode || FbxGeometryElement::eIndexToDirect == refMode)
                    {
                        directIndex = pMesh->GetTextureUVIndex(polygon, polyVert);
                    }

                }
                // If we got a UV index
                if (directIndex != -1)
                {
                    FbxVector2 uv = geomElementUV->GetDirectArray().GetAt(directIndex);

                    v.uv = XMFLOAT2((float)uv.mData[0],
                        (float)uv.mData[1]);
                }
                // Grab normals
                int normElementCount = pMesh->GetElementNormalCount();

                for (int normElement = 0; normElement < normElementCount; normElement++)
                {
                    FbxGeometryElementNormal* geomElementNormal = pMesh->GetElementNormal(normElement);

                    FbxLayerElement::EMappingMode mapMode = geomElementNormal->GetMappingMode();
                    FbxLayerElement::EReferenceMode refMode = geomElementNormal->GetReferenceMode();

                    int directIndex = -1;

                    if (FbxGeometryElement::eByPolygonVertex == mapMode)
                    {
                        if (FbxGeometryElement::eDirect == refMode)
                        {
                            directIndex = vertexID;
                        }
                        else if (FbxGeometryElement::eIndexToDirect == refMode)
                        {
                            directIndex = geomElementNormal->GetIndexArray().GetAt(vertexID);
                        }
                    }

                    // If we got an index
                    if (directIndex != 1)
                    {
                        FbxVector4 norm = geomElementNormal->GetDirectArray().GetAt(directIndex);

                        v.normal = XMFLOAT3((float)norm.mData[0],
                            (float)norm.mData[1],
                            (float)norm.mData[2]);

                    }
                }
                //去重
                size_t size = mesh.vertices.size();
                size_t i;

                for (i = 0; i < size; i++)
                {
                    if (v.index == mesh.vertices[i].index)
                    {
                        break;
                    }
                }

                if (i == size)
                {
                    mesh.vertices.push_back(v);
                }

                mesh.indices.push_back(i);
                
                ++vertexID;

            }
        }
    }
}

inline void PrintNode(FbxNode* pNode,m_Mesh& mesh)
{
   
    FbxMesh* pMesh = pNode->GetMesh();
    if (pMesh != NULL)
    {
        ProcessMesh(pMesh,mesh);
        return ;
    }
    
    // Recursively print the children.
    for (int j = 0; j < pNode->GetChildCount(); j++)
        PrintNode(pNode->GetChild(j),mesh);

}