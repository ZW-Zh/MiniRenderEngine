//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
#include "Metalib.h"
#include "stdafx.h"
#include "D3D12BetterSimpleBox.h"
#include <DXRuntime/FrameResource.h>
#include <Component/Camera.h>
#include <Resource/DefaultBuffer.h>
#include <Shader/RasterShader.h>
#include <Shader/PSOManager.h>
#include <Resource/MeshHelper.h>
#include <Utility/DebugHelper.h>
#include <Utility/DDSTextureLoader12.h>
#include <d3d12.h>

D3D12BetterSimpleBox::D3D12BetterSimpleBox(uint32_t width, uint32_t height, std::wstring name)
	: DXSample(width, height, name),
	  m_viewport(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)),
	  m_scissorRect(0, 0, static_cast<LONG>(width), static_cast<LONG>(height)) {
}
void D3D12BetterSimpleBox::OnInit() {
	LoadPipeline();
	LoadMeshData();
	LoadAssets();
	
}

// Load the rendering pipeline dependencies.
void D3D12BetterSimpleBox::LoadPipeline() {
	// create device;
	device = std::make_unique<Device>();
	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	ThrowIfFailed(device->DxDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));

	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.Width = m_width;
	swapChainDesc.Height = m_height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	ComPtr<IDXGISwapChain1> swapChain;
	ThrowIfFailed(device->DxgiFactory()->CreateSwapChainForHwnd(
		m_commandQueue.Get(),// Swap chain needs the queue so that it can force a flush on it.
		Win32Application::GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain));

	// This sample does not support fullscreen transitions.
	ThrowIfFailed(device->DxgiFactory()->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER));

	ThrowIfFailed(swapChain.As(&m_swapChain));
	m_backBufferIndex = 0;

	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FrameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(device->DxDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));

		m_rtvDescriptorSize = device->DxDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
		dsvHeapDesc.NumDescriptors = FrameCount;
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(device->DxDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap)));

		m_dsvDescriptorSize = device->DxDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

		D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
		srvHeapDesc.NumDescriptors = 1;
		srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		ThrowIfFailed(device->DxDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_srvHeap)));
		m_srvDescriptorSize = device->DxDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		
	}

	// Create frame resources.
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());

		// Create a RTV for each frame.
		for (uint32_t n = 0; n < FrameCount; n++) {
			m_renderTargets[n] = std::unique_ptr<Texture>(new Texture(device.get(), m_swapChain.Get(), n));
			m_depthTargets[n] = std::unique_ptr<Texture>(
				new Texture(
					device.get(),
					m_scissorRect.right,
					m_scissorRect.bottom,
					DXGI_FORMAT_D32_FLOAT,
					TextureDimension::Tex2D,
					1,
					1,
					Texture::TextureUsage::DepthStencil,
					D3D12_RESOURCE_STATE_DEPTH_READ));

			device->DxDevice()->CreateRenderTargetView(m_renderTargets[n]->GetResource(), nullptr, rtvHandle);
			device->DxDevice()->CreateDepthStencilView(m_depthTargets[n]->GetResource(), nullptr, dsvHandle);
			rtvHandle.Offset(1, m_rtvDescriptorSize);
			dsvHandle.Offset(1, m_dsvDescriptorSize);
		}
	}
	// Init FrameResources
	for (auto&& i : frameResources) {
		i = std::unique_ptr<FrameResource>(new FrameResource(device.get()));
	}
}
static Vertex vertexSample;
// Cube model generated from Unity3D
static std::vector<XMFLOAT3> vertices;
static std::vector<uint> indices;
m_Mesh mesh;
void D3D12BetterSimpleBox::LoadMeshData()
{
	// Change the following filename to a suitable filename value.
    const char* lFilename = "./model/megaphone/Megaphone_01_1k.fbx";

    // Initialize the SDK manager. This object handles all our memory management.
    FbxManager* lSdkManager = FbxManager::Create();

    // Create the IO settings object.
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create an importer using the SDK manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Use the first argument as the filename for the importer.
    if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) {
        OutputDebugPrintf("Call to FbxImporter::Initialize() failed.\n");
        OutputDebugPrintf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
        exit(-1);
    }

    // Create a new scene so that it can be populated by the imported file.
    FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

    // Import the contents of the file into the scene.
    lImporter->Import(lScene);

    // The file is imported; so get rid of the importer.
    lImporter->Destroy();

    // Print the nodes of the scene and their attributes recursively.
    // Note that we are not printing the root node because it should
    // not contain any attributes.
    FbxNode* lRootNode = lScene->GetRootNode();
    
    if (lRootNode) {
        for (int i = 0; i < lRootNode->GetChildCount(); i++)
            PrintNode(lRootNode->GetChild(i),mesh);
    }
	for(auto i : mesh.vertices)
	{
		vertices.push_back(i.position);
	}
	indices = mesh.indices;
    // Destroy the SDK manager and all the other objects it was handling.
    lSdkManager->Destroy();

	//load texture

	ThrowIfFailed(DirectX::LoadDDSTextureFromFile(device->DxDevice(), L"./model/megaphone/textures/Megaphone_01_diff_1k.dds", tex.ReleaseAndGetAddressOf(), ddsData, subresources));
}

static UploadBuffer* BuildCubeVertex(Device* device) {
	size_t VERTEX_COUNT = vertices.size();
	std::vector<vbyte> vertexData(vertexSample.structSize * VERTEX_COUNT);
	vbyte* vertexDataPtr = vertexData.data();
	for (size_t i = 0; i < VERTEX_COUNT; ++i) {
		XMFLOAT3 vert = vertices[i];
		vertexSample.position.Get(vertexDataPtr) = vert;
		XMFLOAT4 color(
			vert.x + 0.5f,
			vert.y + 0.5f,
			vert.z + 0.5f,
			1);
		vertexSample.color.Get(vertexDataPtr) = color;
		vertexDataPtr += vertexSample.structSize;
	}
	
	UploadBuffer* vertBuffer = new UploadBuffer(
		device,
		vertexData.size());
	vertBuffer->CopyData(0, vertexData);
	return vertBuffer;
	
}
static UploadBuffer* BuildCubeIndices(Device* device) {
	UploadBuffer* indBuffer = new UploadBuffer(
		device,
		indices.size() * sizeof(uint));
	indBuffer->CopyData(0, {reinterpret_cast<vbyte const*>(indices.data()), indices.size() * sizeof(uint)});
	return indBuffer;
}

// Load the sample assets.
void D3D12BetterSimpleBox::LoadAssets() {
	// Create mesh
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ThrowIfFailed(
		device
			->DxDevice()
			->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator.GetAddressOf())));
	ThrowIfFailed(device->DxDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
	ThrowIfFailed(commandList->Close());
	ThrowIfFailed(cmdAllocator->Reset());
	ThrowIfFailed(commandList->Reset(cmdAllocator.Get(), nullptr));
	std::unique_ptr<UploadBuffer> vertexUpload(BuildCubeVertex(device.get()));
	std::unique_ptr<UploadBuffer> indexUpload(BuildCubeIndices(device.get()));
	std::vector<rtti::Struct const*> structs;
	structs.emplace_back(&vertexSample);
	triangleMesh = std::make_unique<Mesh>(
		device.get(),
		structs,
		vertices.size(),
		indices.size());
	// Copy vertex buffer to mesh
	commandList->CopyBufferRegion(
		triangleMesh->VertexBuffers()[0].GetResource(),
		0,
		vertexUpload->GetResource(),
		0,
		vertexUpload->GetByteSize());
	// Copy index buffer to mesh
	commandList->CopyBufferRegion(
		triangleMesh->IndexBuffer().GetResource(),
		0,
		indexUpload->GetResource(),
		0,
		indexUpload->GetByteSize());
	// Build camera
	
	mainCamera = std::make_unique<Camera>();
	mainCamera->Right = Math::Vector3(0.6877694, -1.622736E-05, 0.7259292);
	mainCamera->Up = Math::Vector3(-0.3181089, 0.8988663, 0.301407);
	mainCamera->Forward = Math::Vector3(-0.6525182, -0.438223, 0.6182076);
	mainCamera->Position = Math::Vector3(2.232773, 1.501817, -1.883978);
	mainCamera->SetAspect(static_cast<float>(m_scissorRect.right) / static_cast<float>(m_scissorRect.bottom));
	mainCamera->UpdateViewMatrix();
	mainCamera->UpdateProjectionMatrix();
	ThrowIfFailed(commandList->Close());
	// Execute CommandList
	ID3D12CommandList* ppCommandLists[] = {commandList.Get()};
	m_commandQueue->ExecuteCommandLists(array_count(ppCommandLists), ppCommandLists);
	// Create the pipeline state, which includes compiling and loading shaders.
	{
		std::vector<std::pair<std::string, Shader::Property>> properties;
		properties.emplace_back(//只是创建描述符
			"_Global",
			Shader::Property{
				.type = ShaderVariableType::ConstantBuffer,
				.spaceIndex = 0,
				.registerIndex = 0,
				.arrSize = 0});
		properties.emplace_back(//创建纹理描述符表
			"_Texture",
			Shader::Property{
				.type = ShaderVariableType::SRVDescriptorHeap,
				.spaceIndex = 0,
				.registerIndex = 0,
				.arrSize = 3});
		colorShader = std::unique_ptr<RasterShader>(
			new RasterShader(
				properties,
				device.get()));
		psoManager = std::unique_ptr<PSOManager>(
			new PSOManager(device.get()));
		ComPtr<ID3DBlob> vertexShader;
		ComPtr<ID3DBlob> pixelShader;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		uint32_t compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		uint32_t compileFlags = 0;
#endif
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shader/shaders.hlsl").c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shader/shaders.hlsl").c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));
		colorShader->vsShader = std::move(vertexShader);
		colorShader->psShader = std::move(pixelShader);
		colorShader->rasterizeState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		colorShader->blendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		auto&& depthStencilState = colorShader->depthStencilState;
		depthStencilState.DepthEnable = true;
		depthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		depthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		depthStencilState.StencilEnable = false;
	}

	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	{
		ThrowIfFailed(device->DxDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceValue = 1;
		m_commandQueue->Signal(m_fence.Get(), m_fenceValue);
		if (m_fence->GetCompletedValue() < m_fenceValue) {
			LPCWSTR falseValue = 0;
			HANDLE eventHandle = CreateEventEx(nullptr, falseValue, false, EVENT_ALL_ACCESS);
			ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValue, eventHandle));
			WaitForSingleObject(eventHandle, INFINITE);
			CloseHandle(eventHandle);
		}
	}
}

// Update frame-based values.
void D3D12BetterSimpleBox::OnUpdate() {
}

// Render the scene.
void D3D12BetterSimpleBox::OnRender() {
	// Record all the commands we need to render the scene into the command list.
	auto curFrame = m_backBufferIndex;
	auto nextFrame = (curFrame + 1) % FrameCount;
	auto lastFrame = (nextFrame + 1) % FrameCount;
	// Execute and Present
	frameResources[curFrame]->Execute(
		m_commandQueue.Get(),
		m_fence.Get(),
		m_fenceValue);
	ThrowIfFailed(m_swapChain->Present(0, 0));
	m_backBufferIndex = (m_backBufferIndex + 1) % FrameCount;
	// Signal Frame
	frameResources[curFrame]->Signal(
		m_commandQueue.Get(),
		m_fence.Get());
	// Populate next frame
	PopulateCommandList(*frameResources[nextFrame], nextFrame);
	// Sync last frame
	frameResources[lastFrame]->Sync(
		m_fence.Get());

	// Present the frame.
}

void D3D12BetterSimpleBox::OnDestroy() {
	// Sync all frame
	for (auto&& i : frameResources) {
		i->Sync(m_fence.Get());
	}
}

void D3D12BetterSimpleBox::PopulateCommandList(FrameResource& frameRes, uint frameIndex) {
	auto cmdListHandle = frameRes.Command();
	auto cmdList = cmdListHandle.CmdList();
	// Set necessary state.

	stateTracker.RecordState(m_renderTargets[frameIndex].get(), D3D12_RESOURCE_STATE_RENDER_TARGET);
	stateTracker.RecordState(m_depthTargets[frameIndex].get(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
	stateTracker.UpdateState(cmdList);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, m_rtvDescriptorSize);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(m_dsvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, m_dsvDescriptorSize);
	frameRes.SetRenderTarget(
		m_renderTargets[frameIndex].get(),
		&rtvHandle,
		&dsvHandle);
	frameRes.ClearRTV(rtvHandle);
	frameRes.ClearDSV(dsvHandle);
	// Record commands.
	DXGI_FORMAT colorFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT depthFormat = DXGI_FORMAT_D32_FLOAT;

	Math::Matrix4 viewProjMatrix = mainCamera->Proj * mainCamera->View;
	auto constBuffer = frameRes.AllocateConstBuffer({reinterpret_cast<uint8_t const*>(&viewProjMatrix), sizeof(viewProjMatrix)});
	bindProperties.clear();
	bindProperties.emplace_back("_Global", constBuffer);
	frameRes.DrawMesh(
		colorShader.get(),
		psoManager.get(),
		triangleMesh.get(),
		colorFormat,
		depthFormat,
		bindProperties);
	stateTracker.RestoreState(cmdList);
}
D3D12BetterSimpleBox::~D3D12BetterSimpleBox() {}
