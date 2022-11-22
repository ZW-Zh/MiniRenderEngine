//*********************************************************
//0
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include "DXSample.h"
#include <Resource/Mesh.h>
#include <DXRuntime/Device.h>
#include <Resource/UploadBuffer.h>
#include <Resource/Texture.h>
#include <DXRuntime/ResourceStateTracker.h>
#include <DXRuntime/BindProperty.h>
#include <memory>
#include <stdint.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>

using namespace DirectX;
// Note that while ComPtr is used to manage the lifetime of resources on the CPU,
// it has no understanding of the lifetime of resources on the GPU. Apps must account
// for the GPU lifetime of resources to avoid destroying objects that may still be
// referenced by the GPU.
// An example of this can be found in the class method: OnDestroy().
using Microsoft::WRL::ComPtr;
class FrameResource;
class Camera;
class PSOManager;
class RasterShader;
class CommandListHandle;
class DefaultBuffer;
struct Vertex : public rtti::Struct {//struct里按照
	rtti::Var<XMFLOAT3> position = "POSITION";
	rtti::Var<XMFLOAT4> color = "COLOR";
	rtti::Var<XMFLOAT3> normal = "NORMAL";
	rtti::Var<XMFLOAT2> texcoord= "TEXCOORD";
};
class D3D12BetterSimpleBox : public DXSample {
public:
	D3D12BetterSimpleBox(uint32_t width, uint32_t height, std::wstring name);
	D3D12BetterSimpleBox(D3D12BetterSimpleBox const&) = delete;
	D3D12BetterSimpleBox(D3D12BetterSimpleBox&&) = delete;
	void OnInit() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnDestroy() override;
	
	~D3D12BetterSimpleBox();
	
private:
	static const uint32_t FrameCount = 3;
	std::unique_ptr<Device> device;
	std::unique_ptr<Camera> mainCamera;
	// Pipeline objects.
	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_scissorRect;
	ComPtr<IDXGISwapChain3> m_swapChain;
	std::unique_ptr<Texture> m_renderTargets[FrameCount];
	std::unique_ptr<Texture> m_depthTargets[FrameCount];
	std::unique_ptr<Texture> m_tex;

	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12DescriptorHeap> m_dsvHeap;
	std::unique_ptr<DescriptorHeap> srvDescHeap;
	//着色器资源描述符
	//ComPtr<ID3D12DescriptorHeap> m_srvHeap;
	//纹理相关,存进m_tex
	//ComPtr<ID3D12Resource> tex;
	std::unique_ptr<uint8_t[]> ddsData;
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;

	std::unique_ptr<PSOManager> psoManager;
	std::unique_ptr<RasterShader> colorShader;
	uint32_t m_rtvDescriptorSize;
	uint32_t m_dsvDescriptorSize;
	//着色器资源描述符大小
	uint32_t m_srvDescriptorSize;

	std::unique_ptr<FrameResource> frameResources[FrameCount];
	ResourceStateTracker stateTracker;
	// App resources.
	std::unique_ptr<Mesh> triangleMesh;
	// Synchronization objects.
	uint32_t m_backBufferIndex;
	ComPtr<ID3D12Fence> m_fence;
	uint64_t m_fenceValue;
	std::vector<BindProperty> bindProperties;
	void LoadPipeline();
	void LoadAssets();
	void LoadMeshData();
	void PopulateCommandList(FrameResource& frameRes, uint frameIndex);
	//键盘鼠标事件
	void OnKeyboardInput(const GameTimer& gt);
	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
    virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
    virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
	//上次按下的鼠标位置
	POINT mLastMousePos;

	//imgui
	void ImGUIInit();
	void ImGUIRender();
	void ImGUIDestory();
};
