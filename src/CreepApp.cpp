//***************************************************************************************
// CreepApp.cpp by Frank Luna (C) 2015 All Rights Reserved.
//***************************************************************************************

#include "Structure/d3dApp.h"
#include "Utility/MathHelper.h"
#include "Structure/UploadBuffer.h"
#include "FrameResource.h"
#include "Utility/MeshHelper.h"
#include <DirectXMath.h>
#include <d3d12.h>
#include <debugapi.h>
#include <memory>
#include <string>
#include <winuser.h>
#include "Component/Camera.h"
#include "Utility/GeometryGenerator.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

const int gNumFrameResources = 3;

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
	RenderItem() = default;

    // World matrix of the shape that describes the object's local space
    // relative to the world space, which defines the position, orientation,
    // and scale of the object in the world.
    XMFLOAT4X4 World = MathHelper::Identity4x4();

	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
	// Because we have an object cbuffer for each FrameResource, we have to apply the
	// update to each FrameResource.  Thus, when we modify obect data we should set 
	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
};

enum class RenderLayer : int
{
	Opaque = 0,
	Sky,
	Count
};

class CreepApp : public D3DApp
{
public:
    CreepApp(HINSTANCE hInstance);
    CreepApp(const CreepApp& rhs) = delete;
    CreepApp& operator=(const CreepApp& rhs) = delete;
    ~CreepApp();

    virtual bool Initialize()override;

private:
    virtual void OnResize()override;
    virtual void Update(const GameTimer& gt)override;
    virtual void Draw(const GameTimer& gt)override;

    virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
    virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
    virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

    void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	void LoadTexAndGeo(int modelIndex);
    void BuildRootSignature();
	void BuildDescriptorHeaps();
    void BuildShadersAndInputLayout();
    //void BuildShapeGeometry();
    void BuildPSOs();
    void BuildFrameResources();
    void BuildMaterials();
    void BuildRenderItems();
    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:

    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    UINT mCbvSrvDescriptorSize = 0;

    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    //ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;
 	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];

    PassConstants mMainPassCB;

	// XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
	// XMFLOAT4X4 mView = MathHelper::Identity4x4();
	// XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	Camera mCamera;

	

    POINT mLastMousePos;

	int lastModelIndex = -1;//用于模型切换
	int lastCameraIndex = -1;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
#define _CRTDBG_MAP_ALLOC   // Enable run-time memory check for debug builds.
#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    try
    {
        CreepApp theApp(hInstance);
        if(!theApp.Initialize())
            return 0;

        return theApp.Run();
    }
    catch(DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }
}

CreepApp::CreepApp(HINSTANCE hInstance)
    : D3DApp(hInstance)
{
}

CreepApp::~CreepApp()
{

    if(md3dDevice != nullptr)
        FlushCommandQueue();
	 // Cleanup
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
	
	if(mRootSignature){mRootSignature->Release();mRootSignature.Detach();}
	if(mSrvDescriptorHeap){mSrvDescriptorHeap->Release();mSrvDescriptorHeap.Detach();}
	for(auto& i : mPSOs)
	{
		if(i.second){i.second->Release();i.second.Detach();}
	}
	
	for(auto& i:mTextures)
	{
		if(i.second) i.second=nullptr;
	}
}

bool CreepApp::Initialize()
{
    if(!D3DApp::Initialize())
        return false;

    // Reset the command list to prep for initialization commands.
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

    // Get the increment size of a descriptor in this heap type.  This is hardware specific, 
	// so we have to query this information.
    mCbvSrvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//读取文件夹
	Gui::GetModel();

	//LoadTexAndGeo(Gui::currentModelIndex);
    BuildRootSignature();
	BuildDescriptorHeaps();
    BuildShadersAndInputLayout();
    //BuildShapeGeometry();
	BuildMaterials();
    //BuildRenderItems();
    //BuildFrameResources();
    BuildPSOs();

    // Execute the initialization commands.
    ThrowIfFailed(mCommandList->Close());
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // Wait until initialization is complete.
    FlushCommandQueue();

    return true;
}
 
void CreepApp::OnResize()
{
    D3DApp::OnResize();

    // The window resized, so update the aspect ratio and recompute the projection matrix.
    // XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 0.05f, 100.0f);
    // XMStoreFloat4x4(&mProj, P);
	mCamera.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 0.1f, 1000.0f);
}

void CreepApp::LoadTexAndGeo(int modelIndex)
{
	if(modelIndex != lastModelIndex)
	{
		// Flush before changing any resources.
		FlushCommandQueue();

    	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
	
		auto modelTex = std::make_unique<Texture>();
		
		wstring modelName = Gui::modelFilePath[modelIndex].substr(8);
		wstring texPath = Gui::modelFilePath[modelIndex]+L"/textures/"+modelName+L".dds";
		wstring wmodelPath = Gui::modelFilePath[modelIndex]+L"/"+modelName+L".fbx";
		modelTex->Filename = texPath;
		modelTex->Name = "modelTex";
	    
        string modelPath = d3dUtil::wstringTostring(wmodelPath);
		//load texture
		modelTex->createTexture(md3dDevice.Get());
		
		m_Mesh mesh;
		loadModel(modelPath, mesh);
		if(mesh.vertices.size() != 0)
		{
			//模型也加载成功了再上传
			mTextures[modelTex->Name] = std::move(modelTex);
			//uploadtex
			mTextures["modelTex"]->uploadTex(md3dDevice.Get(), mCommandList.Get());
			SubmeshGeometry modelSubmesh;
			modelSubmesh.IndexCount = mesh.indices.size();
			modelSubmesh.StartIndexLocation = 0;
			modelSubmesh.BaseVertexLocation = 0;
			std::vector<Vertex> vertices(mesh.vertices.size());
			for(size_t i = 0; i < mesh.vertices.size(); ++i)
			{
				vertices[i].Pos = mesh.vertices[i].position;
				vertices[i].Normal = mesh.vertices[i].normal;
				vertices[i].TexC = mesh.vertices[i].uv;
			}
			std::vector<std::uint16_t> indices;
			indices.assign(mesh.indices.begin(),mesh.indices.end());
			
			const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
			const UINT ibByteSize = (UINT)indices.size()  * sizeof(std::uint16_t);

			auto geo = std::make_unique<MeshGeometry>();
			geo->Name = "modelGeo";

			ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
			CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

			ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
			CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

			geo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
				mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

			geo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
				mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

			geo->VertexByteStride = sizeof(Vertex);
			geo->VertexBufferByteSize = vbByteSize;
			geo->IndexFormat = DXGI_FORMAT_R16_UINT;
			geo->IndexBufferByteSize = ibByteSize;

			geo->DrawArgs["model"] = modelSubmesh;

			mGeometries[geo->Name] = std::move(geo);

			//重新创建srv
			CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
			hDescriptor.Offset(1,mCbvSrvDescriptorSize);

			auto modelTexRes = mTextures["modelTex"]->Resource;
		
			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Format = modelTexRes->GetDesc().Format;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = modelTexRes->GetDesc().MipLevels;
			srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

			md3dDevice->CreateShaderResourceView(modelTexRes.Get(), &srvDesc, hDescriptor);
			
			//skybox
			auto cubeMap = std::make_unique<Texture>();
			cubeMap->Name = "skyTex";
			cubeMap->Filename = L"./texture/cubemap.dds";
			cubeMap->createTexture(md3dDevice.Get());
			//模型也加载成功了再上传
			mTextures[cubeMap->Name] = std::move(cubeMap);
			//uploadtex，上传到gpu memory
			mTextures["skyTex"]->uploadTex(md3dDevice.Get(), mCommandList.Get());

			//CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
			hDescriptor.Offset(1,mCbvSrvDescriptorSize);//gui，modeltex

			auto cubeTexRes = mTextures["skyTex"]->Resource;
		
			D3D12_SHADER_RESOURCE_VIEW_DESC cubeSrvDesc = {};
			cubeSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			cubeSrvDesc.Format = cubeTexRes->GetDesc().Format;
			cubeSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
			cubeSrvDesc.Texture2D.MostDetailedMip = 0;
			cubeSrvDesc.Texture2D.MipLevels = cubeTexRes->GetDesc().MipLevels;
			cubeSrvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

			md3dDevice->CreateShaderResourceView(cubeTexRes.Get(), &cubeSrvDesc, hDescriptor);

			//创建天空geo
			GeometryGenerator geoGen;
			GeometryGenerator::MeshData sphere = geoGen.CreateSphere(0.5f, 20, 20);

			SubmeshGeometry sphereSubmesh;
			sphereSubmesh.IndexCount = (UINT)sphere.Indices32.size();
			sphereSubmesh.StartIndexLocation = 0;
			sphereSubmesh.BaseVertexLocation = 0;

			std::vector<Vertex> cube_vertices(sphere.Vertices.size());
			for(size_t i = 0; i < sphere.Vertices.size(); ++i)
			{
				cube_vertices[i].Pos = sphere.Vertices[i].Position;
				cube_vertices[i].Normal = sphere.Vertices[i].Normal;
				cube_vertices[i].TexC = sphere.Vertices[i].TexC;
			}

			std::vector<std::uint16_t> cube_indices;
			cube_indices.insert(cube_indices.end(), std::begin(sphere.GetIndices16()), std::end(sphere.GetIndices16()));
		
			const UINT cube_vbByteSize = (UINT)cube_vertices.size() * sizeof(Vertex);
			const UINT cube_ibByteSize = (UINT)cube_indices.size()  * sizeof(std::uint16_t);

			auto cube_geo = std::make_unique<MeshGeometry>();
			cube_geo->Name = "skyGeo";

			ThrowIfFailed(D3DCreateBlob(cube_vbByteSize, &cube_geo->VertexBufferCPU));
			CopyMemory(cube_geo->VertexBufferCPU->GetBufferPointer(), cube_vertices.data(), cube_vbByteSize);

			ThrowIfFailed(D3DCreateBlob(cube_ibByteSize, &cube_geo->IndexBufferCPU));
			CopyMemory(cube_geo->IndexBufferCPU->GetBufferPointer(), cube_indices.data(), cube_ibByteSize);

			cube_geo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
				mCommandList.Get(), cube_vertices.data(), cube_vbByteSize, cube_geo->VertexBufferUploader);

			cube_geo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
				mCommandList.Get(), cube_indices.data(), cube_ibByteSize, cube_geo->IndexBufferUploader);

			cube_geo->VertexByteStride = sizeof(Vertex);
			cube_geo->VertexBufferByteSize = cube_vbByteSize;
			cube_geo->IndexFormat = DXGI_FORMAT_R16_UINT;
			cube_geo->IndexBufferByteSize = cube_ibByteSize;

			cube_geo->DrawArgs["sky"] = sphereSubmesh;

			mGeometries[cube_geo->Name] = std::move(cube_geo);
			//重新创建renderitem
			mAllRitems.clear();
			mRitemLayer[(int)RenderLayer::Opaque].clear();
			mRitemLayer[(int)RenderLayer::Sky].clear();
			BuildRenderItems();
			//重新创建帧资源
			BuildFrameResources();
			//成功了换模型下标
			lastModelIndex = modelIndex;
		}else {
			OutputDebugStringA("Failed to load model!");
			Gui::currentModelIndex = lastModelIndex;
		}
		

		// Execute the initialization commands.
		ThrowIfFailed(mCommandList->Close());
		ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
		mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	}

}

void CreepApp::BuildRootSignature()
{
	CD3DX12_DESCRIPTOR_RANGE texTable[2];
	// 一个模型srv，一个cubemap srv
	texTable[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0,0);
	texTable[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV,1,1,0);
    // Root parameter can be a table, root descriptor or root constants.
    CD3DX12_ROOT_PARAMETER slotRootParameter[4];

	// Perfomance TIP: Order from most frequent to least frequent.
	
	slotRootParameter[0].InitAsConstantBufferView(0);//b0
    slotRootParameter[1].InitAsConstantBufferView(1);//b1
    slotRootParameter[2].InitAsShaderResourceView(0, 1);//t0 space1
	slotRootParameter[3].InitAsDescriptorTable(2, texTable, D3D12_SHADER_VISIBILITY_PIXEL);//t0
	

	auto staticSamplers = GetStaticSamplers();

    // A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter,
		(UINT)staticSamplers.size(), staticSamplers.data(),
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
    ComPtr<ID3DBlob> serializedRootSig = nullptr;
    ComPtr<ID3DBlob> errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
        serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

    if(errorBlob != nullptr)
    {
        ::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    }
    ThrowIfFailed(hr);

    ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
        serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(mRootSignature.GetAddressOf())));
}

void CreepApp::BuildDescriptorHeaps()
{
	//
	// Create the SRV heap. imgui还有一个
	//
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 3;//imgui,model,sky
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

	// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(mhMainWnd);
    ImGui_ImplDX12_Init(md3dDevice.Get(), SwapChainBufferCount,
        mBackBufferFormat, mSrvDescriptorHeap.Get(),
        mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
        mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	
}

void CreepApp::BuildShadersAndInputLayout()
{
	const D3D_SHADER_MACRO alphaTestDefines[] =
	{
		"ALPHA_TEST", "1",
		NULL, NULL
	};

	mShaders["standardVS"] = d3dUtil::CompileShader(L"Shader/Default.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shader/Default.hlsl", nullptr, "PS", "ps_5_1");
	
	mShaders["skyVS"] = d3dUtil::CompileShader(L"Shader/Sky.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["skyPS"] = d3dUtil::CompileShader(L"Shader/Sky.hlsl", nullptr, "PS", "ps_5_1");

    mInputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
}


void CreepApp::BuildPSOs()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

	//
	// PSO for opaque objects.
	//
    ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaquePsoDesc.pRootSignature = mRootSignature.Get();
	opaquePsoDesc.VS = 
	{ 
		reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()), 
		mShaders["standardVS"]->GetBufferSize()
	};
	opaquePsoDesc.PS = 
	{ 
		reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
		mShaders["opaquePS"]->GetBufferSize()
	};
	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	opaquePsoDesc.SampleMask = UINT_MAX;
	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaquePsoDesc.NumRenderTargets = 1;
	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
	opaquePsoDesc.SampleDesc.Count = 1;
	opaquePsoDesc.SampleDesc.Quality = 0;
	opaquePsoDesc.DSVFormat = mDepthStencilFormat;

    ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mPSOs["opaque"])));

	D3D12_GRAPHICS_PIPELINE_STATE_DESC msaaPsoDesc = opaquePsoDesc;
	msaaPsoDesc.SampleDesc.Count = 4;
	
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&msaaPsoDesc, IID_PPV_ARGS(&mPSOs["msaa4x"])));

	//
	// PSO for sky.
	//
	D3D12_GRAPHICS_PIPELINE_STATE_DESC skyPsoDesc = opaquePsoDesc;

	// The camera is inside the sky sphere, so just turn off culling.
	skyPsoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

	// Make sure the depth function is LESS_EQUAL and not just LESS.  
	// Otherwise, the normalized depth values at z = 1 (NDC) will 
	// fail the depth test if the depth buffer was cleared to 1.
	skyPsoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	skyPsoDesc.pRootSignature = mRootSignature.Get();
	skyPsoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["skyVS"]->GetBufferPointer()),
		mShaders["skyVS"]->GetBufferSize()
	};
	skyPsoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["skyPS"]->GetBufferPointer()),
		mShaders["skyPS"]->GetBufferSize()
	};
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&skyPsoDesc, IID_PPV_ARGS(&mPSOs["sky"])));
	
	//msaa_sky
	D3D12_GRAPHICS_PIPELINE_STATE_DESC msaa_skyPsoDesc = skyPsoDesc;
	msaa_skyPsoDesc.SampleDesc.Count = 4;
	
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&msaa_skyPsoDesc, IID_PPV_ARGS(&mPSOs["msaa_sky"])));

}

void CreepApp::BuildFrameResources()
{
    for(int i = 0; i < gNumFrameResources; ++i)
    {
        mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
            1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
    }
}

void CreepApp::BuildMaterials()
{
	auto woodCrate = std::make_unique<Material>();
	woodCrate->Name = "woodCrate";
	woodCrate->MatCBIndex = 0;
	woodCrate->DiffuseSrvHeapIndex = 0;
	woodCrate->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	woodCrate->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	woodCrate->Roughness = 0.2f;

	mMaterials["woodCrate"] = std::move(woodCrate);

	auto sky = std::make_unique<Material>();
    sky->Name = "sky";
    sky->MatCBIndex = 1;
    sky->DiffuseSrvHeapIndex = 1;
    sky->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    sky->FresnelR0 = XMFLOAT3(0.1f, 0.1f, 0.1f);
    sky->Roughness = 1.0f;

	mMaterials["sky"] = std::move(sky);
}

void CreepApp::BuildRenderItems()
{
	auto skyRitem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&skyRitem->World, XMMatrixScaling(5000.0f, 5000.0f, 5000.0f));
	skyRitem->TexTransform = MathHelper::Identity4x4();
	skyRitem->ObjCBIndex = 0;
	skyRitem->Mat = mMaterials["sky"].get();
	skyRitem->Geo = mGeometries["skyGeo"].get();
	skyRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	skyRitem->IndexCount = skyRitem->Geo->DrawArgs["sky"].IndexCount;
	skyRitem->StartIndexLocation = skyRitem->Geo->DrawArgs["sky"].StartIndexLocation;
	skyRitem->BaseVertexLocation = skyRitem->Geo->DrawArgs["sky"].BaseVertexLocation;

	mRitemLayer[(int)RenderLayer::Sky].push_back(skyRitem.get());
	mAllRitems.push_back(std::move(skyRitem));

	auto modelRitem = std::make_unique<RenderItem>();
	modelRitem->World = MathHelper::Identity4x4();
	modelRitem->TexTransform = MathHelper::Identity4x4();
	modelRitem->ObjCBIndex = 0;
	modelRitem->Mat = mMaterials["woodCrate"].get();
	modelRitem->Geo = mGeometries["modelGeo"].get();
	modelRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	modelRitem->IndexCount = modelRitem->Geo->DrawArgs["model"].IndexCount;
	modelRitem->StartIndexLocation = modelRitem->Geo->DrawArgs["model"].StartIndexLocation;
	modelRitem->BaseVertexLocation = modelRitem->Geo->DrawArgs["model"].BaseVertexLocation;
	
	mRitemLayer[(int)RenderLayer::Opaque].push_back(modelRitem.get());
	mAllRitems.push_back(std::move(modelRitem));
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> CreepApp::GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return { 
		pointWrap, pointClamp,
		linearWrap, linearClamp, 
		anisotropicWrap, anisotropicClamp };
}

void CreepApp::Update(const GameTimer& gt)
{
	//加载模型和贴图，为了实时更换
	LoadTexAndGeo(Gui::currentModelIndex);
    OnKeyboardInput(gt);
	UpdateCamera(gt);

    // Cycle through the circular frame resource array.
    mCurrFrameResourceIndex = (mCurrFrameResourceIndex + 1) % gNumFrameResources;
    mCurrFrameResource = mFrameResources[mCurrFrameResourceIndex].get();

    // Has the GPU finished processing the commands of the current frame resource?
    // If not, wait until the GPU has completed commands up to this fence point.
    if(mCurrFrameResource->Fence != 0 && mFence->GetCompletedValue() < mCurrFrameResource->Fence)
    {
        HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
        ThrowIfFailed(mFence->SetEventOnCompletion(mCurrFrameResource->Fence, eventHandle));
        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
	
	AnimateMaterials(gt);
	UpdateObjectCBs(gt);
	UpdateMaterialCBs(gt);
	UpdateMainPassCB(gt);

}

void CreepApp::Draw(const GameTimer& gt)
{
    auto cmdListAlloc = mCurrFrameResource->CmdListAlloc;
	
    // Reuse the memory associated with command recording.
    // We can only reset when the associated command lists have finished execution on the GPU.
    ThrowIfFailed(cmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque"].Get()));

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);
	if(m4xMsaaState)
	{
		ImGui_ImplDX12_SetPipelineSamplesCount(4);
		m_msaaHelper->Prepare(mCommandList.Get());
		
		auto rtvDescriptor = m_msaaHelper->GetMSAARenderTargetView();
		auto dsvDescriptor = m_msaaHelper->GetMSAADepthStencilView();
		mCommandList->OMSetRenderTargets(1, &rtvDescriptor, FALSE, &dsvDescriptor);
		mCommandList->ClearRenderTargetView(rtvDescriptor, Colors::LightSteelBlue, 0, nullptr);
		mCommandList->ClearDepthStencilView(dsvDescriptor, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		//设置根签名和常量缓冲区
		ID3D12DescriptorHeap* descriptorHeaps[] = { mSrvDescriptorHeap.Get() };
		mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		mCommandList->SetGraphicsRootSignature(mRootSignature.Get());
		//RootParameterIndex对应根签名参数下标
		//先绑定cbv
		auto passCB = mCurrFrameResource->PassCB->Resource();
		mCommandList->SetGraphicsRootConstantBufferView(1, passCB->GetGPUVirtualAddress());

		auto matBuffer = mCurrFrameResource->MaterialBuffer->Resource();
		mCommandList->SetGraphicsRootShaderResourceView(2, matBuffer->GetGPUVirtualAddress());

		CD3DX12_GPU_DESCRIPTOR_HANDLE texDescriptor(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		texDescriptor.Offset(1, mCbvSrvDescriptorSize);//0是ui的srv然后modeltex，cubetex
		mCommandList->SetGraphicsRootDescriptorTable(3, texDescriptor);


		mCommandList->SetPipelineState(mPSOs["msaa4x"].Get());
		DrawRenderItems(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Opaque]);

		mCommandList->SetPipelineState(mPSOs["sky"].Get());
		DrawRenderItems(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Sky]);

		// Start the Dear ImGui frame
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		Gui::setGUI();
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), mCommandList.Get());
		
		m_msaaHelper->Resolve(mCommandList.Get(), CurrentBackBuffer(),D3D12_RESOURCE_STATE_PRESENT);

	}else {
		ImGui_ImplDX12_SetPipelineSamplesCount(1);

		// Indicate a state transition on the resource usage.
		mCommandList->ResourceBarrier(1, get_rvalue_ptr(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET)));

		// Clear the back buffer and depth buffer.
		mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
		mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		// Specify the buffers we are going to render to.
		mCommandList->OMSetRenderTargets(1, get_rvalue_ptr(CurrentBackBufferView()), true, get_rvalue_ptr(DepthStencilView()));

		ID3D12DescriptorHeap* descriptorHeaps[] = { mSrvDescriptorHeap.Get() };
		mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

		mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

		auto passCB = mCurrFrameResource->PassCB->Resource();
		mCommandList->SetGraphicsRootConstantBufferView(1, passCB->GetGPUVirtualAddress());

		auto matBuffer = mCurrFrameResource->MaterialBuffer->Resource();
		mCommandList->SetGraphicsRootShaderResourceView(2, matBuffer->GetGPUVirtualAddress());

		CD3DX12_GPU_DESCRIPTOR_HANDLE texDescriptor(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		texDescriptor.Offset(1, mCbvSrvDescriptorSize);//0是ui的srv然后modeltex，cubetex
		mCommandList->SetGraphicsRootDescriptorTable(3, texDescriptor);

		DrawRenderItems(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Opaque]);

		mCommandList->SetPipelineState(mPSOs["sky"].Get());
		DrawRenderItems(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Sky]);
		
		// Start the Dear ImGui frame
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		Gui::setGUI();

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), mCommandList.Get());

		// Indicate a state transition on the resource usage.
		mCommandList->ResourceBarrier(1, get_rvalue_ptr(CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT)));
	}
	
    // Done recording commands.
    ThrowIfFailed(mCommandList->Close());

    // Add the command list to the queue for execution.
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // Swap the back and front buffers
    ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

    // Advance the fence value to mark commands up to this fence point.
    mCurrFrameResource->Fence = ++mCurrentFence;

    // Add an instruction to the command queue to set a new fence point. 
    // Because we are on the GPU timeline, the new fence point won't be 
    // set until the GPU finishes processing all the commands prior to this Signal().
    mCommandQueue->Signal(mFence.Get(), mCurrentFence);
}
void CreepApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems)
{
	//绑定帧资源
    UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
    
	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
	
    // For each render item...
    for(size_t i = 0; i < ritems.size(); ++i)
    {
        auto ri = ritems[i];

        cmdList->IASetVertexBuffers(0, 1, get_rvalue_ptr(ri->Geo->VertexBufferView()));
        cmdList->IASetIndexBuffer(get_rvalue_ptr(ri->Geo->IndexBufferView()));
        cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

        D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex*objCBByteSize;
		
		cmdList->SetGraphicsRootConstantBufferView(0, objCBAddress);
        cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
    }
}

void CreepApp::OnMouseDown(WPARAM btnState, int x, int y)
{
       
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void CreepApp::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void CreepApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	if(!io.WantCaptureMouse)//不是发生在ui上的事件
	{
		if(Gui::currentCameraIndex == 0)
		{
			if((btnState & MK_LBUTTON) != 0)
			{
				// Make each pixel correspond to a quarter of a degree.
				float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
				float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

				// Update angles based on input to orbit camera around box.
				mCamera.mTheta += dx;
				mCamera.mPhi += dy;

				// Restrict the angle mPhi.
				mCamera.mPhi = MathHelper::Clamp(mCamera.mPhi, 0.1f, MathHelper::Pi - 0.1f);
			}
			else if((btnState & MK_RBUTTON) != 0)
			{
				// Make each pixel correspond to 0.2 unit in the scene.
				float dx = 0.05f*static_cast<float>(x - mLastMousePos.x);
				float dy = 0.05f*static_cast<float>(y - mLastMousePos.y);

				// Update the camera radius based on input.
				mCamera.mRadius += dx - dy;

				// Restrict the radius.
				mCamera.mRadius = MathHelper::Clamp(mCamera.mRadius, 0.1f, 150.0f);
			}
			
			
		}
		else if(Gui::currentCameraIndex == 1)
		{
			if((btnState & MK_LBUTTON) != 0)
			{
				// Make each pixel correspond to a quarter of a degree.
				float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
				float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

				mCamera.Pitch(dy);
				mCamera.RotateY(dx);
			}
		}
		mLastMousePos.x = x;
		mLastMousePos.y = y;
	}
}
 
void CreepApp::OnKeyboardInput(const GameTimer& gt)
{
	if(Gui::currentCameraIndex == 1)
	{
		const float dt = gt.DeltaTime();

		if(GetAsyncKeyState('W') & 0x8000)
			mCamera.Walk(10.0f*dt);

		if(GetAsyncKeyState('S') & 0x8000)
			mCamera.Walk(-10.0f*dt);

		if(GetAsyncKeyState('A') & 0x8000)
			mCamera.Strafe(-10.0f*dt);

		if(GetAsyncKeyState('D') & 0x8000)
			mCamera.Strafe(10.0f*dt);

		mCamera.UpdateViewMatrix();
	}
	
}
 
void CreepApp::UpdateCamera(const GameTimer& gt)
{
	if(Gui::currentCameraIndex == 0)
	{
		float x = mCamera.mRadius*sinf(mCamera.mPhi)*cosf(mCamera.mTheta);
		float z = mCamera.mRadius*sinf(mCamera.mPhi)*sinf(mCamera.mTheta);
		float y = mCamera.mRadius*cosf(mCamera.mPhi);
		mCamera.SetPosition(x,y,z);
		mCamera.UpdateCommonViewMatrix();
		std::cout << mCamera.GetPosition3f().x <<" "
		<<mCamera.GetPosition3f().y <<" "
		<<mCamera.GetPosition3f().z <<" "
		<< std::endl;
	}
}

void CreepApp::AnimateMaterials(const GameTimer& gt)
{
	
}

void CreepApp::UpdateObjectCBs(const GameTimer& gt)
{
	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
	for(auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if(e->NumFramesDirty > 0)
		{
			XMMATRIX world = XMLoadFloat4x4(&e->World);
			
			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);

			ObjectConstants objConstants;
			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
			XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));
			objConstants.MaterialIndex = e->Mat->MatCBIndex;

			currObjectCB->CopyData(e->ObjCBIndex, objConstants);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

void CreepApp::UpdateMaterialCBs(const GameTimer& gt)
{
	auto currMaterialBuffer = mCurrFrameResource->MaterialBuffer.get();
	for(auto& e : mMaterials)
	{
		// Only update the cbuffer data if the constants have changed.  If the cbuffer
		// data changes, it needs to be updated for each FrameResource.
		Material* mat = e.second.get();
		if(mat->NumFramesDirty > 0)
		{
			XMMATRIX matTransform = XMLoadFloat4x4(&mat->MatTransform);

			MaterialData matData;
			matData.DiffuseAlbedo = mat->DiffuseAlbedo;
			matData.FresnelR0 = mat->FresnelR0;
			matData.Roughness = mat->Roughness;
			XMStoreFloat4x4(&matData.MatTransform, XMMatrixTranspose(matTransform));
			matData.DiffuseMapIndex = mat->DiffuseSrvHeapIndex;
			currMaterialBuffer->CopyData(mat->MatCBIndex, matData);

			// Next FrameResource need to be updated too.
			mat->NumFramesDirty--;
		}
	}
}

void CreepApp::UpdateMainPassCB(const GameTimer& gt)
{
	XMMATRIX view = mCamera.GetView();
	XMMATRIX proj = mCamera.GetProj();

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(get_rvalue_ptr(XMMatrixDeterminant(view)), view);
	XMMATRIX invProj = XMMatrixInverse(get_rvalue_ptr(XMMatrixDeterminant(proj)), proj);
	XMMATRIX invViewProj = XMMatrixInverse(get_rvalue_ptr(XMMatrixDeterminant(viewProj)), viewProj);

	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	mMainPassCB.EyePosW = mCamera.GetPosition3f();
	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	mMainPassCB.NearZ = 0.1f;
	mMainPassCB.FarZ = 1000.0f;
	mMainPassCB.TotalTime = gt.TotalTime();
	mMainPassCB.DeltaTime = gt.DeltaTime();
	mMainPassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mMainPassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	mMainPassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
	mMainPassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	mMainPassCB.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };

	auto currPassCB = mCurrFrameResource->PassCB.get();
	currPassCB->CopyData(0, mMainPassCB);
}



