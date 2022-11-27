#include "d3dUtil.h"

class MSAAHelper
{
public:
    MSAAHelper(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
        DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D32_FLOAT,
        unsigned int sampleCount = 4);

    void SetDevice(ID3D12Device* device);

    void SizeResources(size_t width, size_t height);

    void ReleaseDevice();

    void Prepare(ID3D12GraphicsCommandList* commandList,
        D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RESOLVE_SOURCE);

    void Resolve(ID3D12GraphicsCommandList* commandList, ID3D12Resource* backBuffer,
        D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_PRESENT);

    void SetWindow(const RECT& rect);

    ID3D12Resource* GetMSAARenderTarget() const { return m_msaaRenderTarget.Get(); }
    ID3D12Resource* GetMSAADepthStencil() const { return m_msaaDepthStencil.Get(); }

    D3D12_CPU_DESCRIPTOR_HANDLE GetMSAARenderTargetView() const
    {
        return m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
    }
    D3D12_CPU_DESCRIPTOR_HANDLE GetMSAADepthStencilView() const
    {
        return m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
    }

    void SetClearColor(DirectX::FXMVECTOR color)
    {
        DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(m_clearColor), color);
    }

    DXGI_FORMAT GetBackBufferFormat() const { return m_backBufferFormat; }
    DXGI_FORMAT GetDepthBufferFormat() const { return m_depthBufferFormat; }
    unsigned int GetSampleCount() const { return m_sampleCount; }

private:
    Microsoft::WRL::ComPtr<ID3D12Device>                m_device;
    Microsoft::WRL::ComPtr<ID3D12Resource>              m_msaaRenderTarget;
    Microsoft::WRL::ComPtr<ID3D12Resource>              m_msaaDepthStencil;
    float                                               m_clearColor[4];

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_rtvDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        m_dsvDescriptorHeap;

    DXGI_FORMAT                                         m_backBufferFormat;
    DXGI_FORMAT                                         m_depthBufferFormat;
    unsigned int                                        m_sampleCount;
    unsigned int                                        m_targetSampleCount;

    size_t                                              m_width;
    size_t                                              m_height;
};