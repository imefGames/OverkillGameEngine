#include <stdafx.h>
#include <graphics\d3d\d3dcontext.h>

#include <engine\components\recttransformcomponent.h>
#include <engine\components\transformcomponent.h>
#include <graphics\renderingcontext.h>
#include <graphics\components\modelcomponent.h>
#include <graphics\model\vertexlist.h>

namespace OK
{
    D3DContext::D3DContext()
        : m_vsync_enabled{ false }
        , m_videoCardMemory{ 0 }
        , m_swapChain{ nullptr }
        , m_device{ nullptr }
        , m_deviceContext{ nullptr }
        , m_renderTargetView{ nullptr }
        , m_depthStencilBuffer{ nullptr }
        , m_depthStencilState{ nullptr }
        , m_depthStencilView{ nullptr }
        , m_rasterState{ nullptr }
        , m_DepthDisabledStencilState{ nullptr }
    {
    }

    D3DContext::~D3DContext()
    {
    }

    bool D3DContext::Initialize(OK::s32 screenWidth, OK::s32 screenHeight, OK::Bool vsync, HWND hwnd, OK::Bool fullscreen, OK::f32 screenDepth, OK::f32 screenNear)
    {
	    HRESULT result;
	    IDXGIFactory* factory;
	    IDXGIAdapter* adapter;
	    IDXGIOutput* adapterOutput;
        OK::u32 numModes, i, numerator, denominator, stringLength;
	    DXGI_MODE_DESC* displayModeList;
	    DXGI_ADAPTER_DESC adapterDesc;
        OK::s32 error;
	    DXGI_SWAP_CHAIN_DESC swapChainDesc;
	    D3D_FEATURE_LEVEL featureLevel;
	    ID3D11Texture2D* backBufferPtr;
	    D3D11_TEXTURE2D_DESC depthBufferDesc;
	    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	    D3D11_RASTERIZER_DESC rasterDesc;
        D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	    D3D11_VIEWPORT viewport;
        OK::f32 fieldOfView, screenAspect;

	    m_vsync_enabled = vsync;
	    result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    result = factory->EnumAdapters(0, &adapter);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    result = adapter->EnumOutputs(0, &adapterOutput);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    displayModeList = new DXGI_MODE_DESC[numModes];
	    if(!displayModeList)
	    {
		    return false;
	    }

	    result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    for(i=0; i<numModes; i++)
	    {
		    if(displayModeList[i].Width == static_cast<OK::u32>(screenWidth))
		    {
			    if(displayModeList[i].Height == static_cast<OK::u32>(screenHeight))
			    {
				    numerator = displayModeList[i].RefreshRate.Numerator;
				    denominator = displayModeList[i].RefreshRate.Denominator;
			    }
		    }
	    }

	    result = adapter->GetDesc(&adapterDesc);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	    error = wcstombs_s(reinterpret_cast<size_t*>(&stringLength), reinterpret_cast<char*>(m_videoCardDescription), 128, adapterDesc.Description, 128);
	    if(error != 0)
	    {
		    return false;
	    }

	    delete [] displayModeList;
	    displayModeList = nullptr;

	    adapterOutput->Release();
	    adapterOutput = nullptr;

	    adapter->Release();
	    adapter = nullptr;

	    factory->Release();
	    factory = nullptr;

        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = screenWidth;
        swapChainDesc.BufferDesc.Height = screenHeight;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	    if(m_vsync_enabled)
	    {
	        swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		    swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	    }
	    else
	    {
	        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	    }
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hwnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
	    if(fullscreen)
	    {
		    swapChainDesc.Windowed = false;
	    }
	    else
	    {
		    swapChainDesc.Windowed = true;
	    }
	    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	    swapChainDesc.Flags = 0;
	    featureLevel = D3D_FEATURE_LEVEL_11_0;
	    result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, 
										       D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
	    if(FAILED(result))
	    {
		    return false;
	    }
	    result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	    if(FAILED(result))
	    {
		    return false;
	    }
	    result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    backBufferPtr->Release();
	    backBufferPtr = nullptr;

	    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	    depthBufferDesc.Width = screenWidth;
	    depthBufferDesc.Height = screenHeight;
	    depthBufferDesc.MipLevels = 1;
	    depthBufferDesc.ArraySize = 1;
	    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	    depthBufferDesc.SampleDesc.Count = 1;
	    depthBufferDesc.SampleDesc.Quality = 0;
	    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	    depthBufferDesc.CPUAccessFlags = 0;
	    depthBufferDesc.MiscFlags = 0;

	    result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	    depthStencilDesc.DepthEnable = true;
	    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	    depthStencilDesc.StencilEnable = true;
	    depthStencilDesc.StencilReadMask = 0xFF;
	    depthStencilDesc.StencilWriteMask = 0xFF;
	    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	    result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	    if(FAILED(result))
	    {
		    return false;
	    }
	    m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	    depthStencilViewDesc.Texture2D.MipSlice = 0;
	    result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	    if(FAILED(result))
	    {
		    return false;
	    }
	    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	    rasterDesc.AntialiasedLineEnable = false;
	    rasterDesc.CullMode = D3D11_CULL_BACK;
	    rasterDesc.DepthBias = 0;
	    rasterDesc.DepthBiasClamp = 0.0f;
	    rasterDesc.DepthClipEnable = true;
	    rasterDesc.FillMode = D3D11_FILL_SOLID;
	    rasterDesc.FrontCounterClockwise = false;
	    rasterDesc.MultisampleEnable = false;
	    rasterDesc.ScissorEnable = false;
	    rasterDesc.SlopeScaledDepthBias = 0.0f;

	    result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	    if(FAILED(result))
	    {
		    return false;
	    }

	    m_deviceContext->RSSetState(m_rasterState);
        viewport.Width = static_cast<OK::f32>(screenWidth);
        viewport.Height = static_cast<OK::f32>(screenHeight);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;

        m_deviceContext->RSSetViewports(1, &viewport);

	    fieldOfView = static_cast<OK::f32>(D3DX_PI) / 4.0f;
	    screenAspect = static_cast<OK::f32>(screenWidth) / static_cast<OK::f32>(screenHeight);

	    D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
        D3DXMatrixIdentity(&m_worldMatrix);
	    D3DXMatrixOrthoLH(&m_orthoMatrix, static_cast<OK::f32>(screenWidth), static_cast<OK::f32>(screenHeight), screenNear, screenDepth);


        ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));
        depthDisabledStencilDesc.DepthEnable = false;
        depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
        depthDisabledStencilDesc.StencilEnable = true;
        depthDisabledStencilDesc.StencilReadMask = 0xFF;
        depthDisabledStencilDesc.StencilWriteMask = 0xFF;
        depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_DepthDisabledStencilState);
        okAssert(SUCCEEDED(result), "Failed to create depth Stencil State.");

        return true;
    }

    void D3DContext::Shutdown()
    {
	    if(m_swapChain != nullptr)
	    {
		    m_swapChain->SetFullscreenState(false, NULL);
	    }

        if (m_DepthDisabledStencilState != nullptr)
        {
            m_DepthDisabledStencilState->Release();
            m_DepthDisabledStencilState = nullptr;
        }

	    if(m_rasterState != nullptr)
	    {
		    m_rasterState->Release();
		    m_rasterState = nullptr;
	    }

	    if(m_depthStencilView != nullptr)
	    {
		    m_depthStencilView->Release();
		    m_depthStencilView = nullptr;
	    }

	    if(m_depthStencilState != nullptr)
	    {
		    m_depthStencilState->Release();
		    m_depthStencilState = nullptr;
	    }

	    if(m_depthStencilBuffer != nullptr)
	    {
		    m_depthStencilBuffer->Release();
		    m_depthStencilBuffer = nullptr;
	    }

	    if(m_renderTargetView != nullptr)
	    {
		    m_renderTargetView->Release();
		    m_renderTargetView = nullptr;
	    }

	    if(m_deviceContext != nullptr)
	    {
		    m_deviceContext->Release();
		    m_deviceContext = nullptr;
	    }

	    if(m_device != nullptr)
	    {
		    m_device->Release();
		    m_device = nullptr;
	    }

	    if(m_swapChain != nullptr)
	    {
		    m_swapChain->Release();
		    m_swapChain = nullptr;
	    }
    }

    void D3DContext::BeginScene(float red, float green, float blue, float alpha)
    {
        OK::f32 color[4];
	    color[0] = red;
	    color[1] = green;
	    color[2] = blue;
	    color[3] = alpha;

	    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
        m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void D3DContext::EndScene()
    {
	    if(m_vsync_enabled)
	    {
		    m_swapChain->Present(1, 0);
	    }
	    else
	    {
		    m_swapChain->Present(0, 0);
	    }
    }

    ID3D11Device* D3DContext::GetDevice()
    {
	    return m_device;
    }

    ID3D11DeviceContext* D3DContext::GetDeviceContext()
    {
	    return m_deviceContext;
    }

    void D3DContext::ComputeRenderingContext(RenderingContext& renderingContext, const TransformComponent* cameraTransform)
    {
        if (cameraTransform != nullptr)
        {
            const OK::Vec4& cameraPosition = cameraTransform->GetPosition();
            const OK::Vec4& cameraRotation = cameraTransform->GetRotationEuler();

            D3DXVECTOR3 up{ 0.0f, 1.0f, 0.0f };
            D3DXVECTOR3 position{ cameraPosition.GetX(), cameraPosition.GetY(), cameraPosition.GetZ() };
            D3DXVECTOR3 lookAt{ 0.0f, 0.0f, 1.0f };

            D3DXMATRIX rotationMatrix;
            D3DXMatrixRotationYawPitchRoll(&rotationMatrix, cameraRotation.GetY(), cameraRotation.GetX(), cameraRotation.GetZ());
            D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
            D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
            lookAt = position + lookAt;

            D3DXMATRIX viewMatrix;
            D3DXMatrixLookAtLH(&renderingContext.m_ViewMatrix, &position, &lookAt, &up);
            renderingContext.m_CameraPosition = cameraPosition;
        }

        renderingContext.m_ProjectionMatrix = m_projectionMatrix;
        renderingContext.m_WorldMatrix = m_worldMatrix;
        renderingContext.m_DeviceContext = m_deviceContext;
        renderingContext.m_Device = m_device;
    }

    void D3DContext::PrepareModelRendering(RenderingContext& renderingContext, VertexList& vertexList, const TransformComponent* modelTransform)
    {
        const OK::Vec4& modelPosition{ modelTransform->GetPosition() };
        const OK::Vec4& modelRotation{ modelTransform->GetRotationEuler() };
        const OK::Vec4& modelScale{ modelTransform->GetScale() };
        D3DXVECTOR3 position{ modelPosition.GetX(), modelPosition.GetY(), modelPosition.GetZ() };
        D3DXVECTOR3 scale{ modelScale.GetX(), modelScale.GetY(), modelScale.GetZ() };
        D3DXQUATERNION rotation;
        D3DXQuaternionRotationYawPitchRoll(&rotation, modelRotation.GetY(), modelRotation.GetX(), modelRotation.GetZ());
        D3DXMatrixTransformation(&renderingContext.m_WorldMatrix, nullptr, nullptr, &scale, nullptr, &rotation, &position);

        OK::u32 stride{ sizeof(VertexData) };
        OK::u32 offset{ 0 };

        ID3D11Buffer * const vertexBuffer = vertexList.GetVertexBuffer();
        renderingContext.m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        renderingContext.m_DeviceContext->IASetIndexBuffer(vertexList.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
        renderingContext.m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    void D3DContext::PrepareSpriteRendering(RenderingContext& renderingContext, VertexList& vertexList, const RectTransformComponent* spriteTransform)
    {
        const OK::Vec4& spritePosition{ spriteTransform->GetPosition() };
        const OK::Vec4& spriteSize{ spriteTransform->GetSize() };

        D3DXVECTOR3 position{ spritePosition.GetX(), spritePosition.GetY(), spritePosition.GetZ() };
        D3DXVECTOR3 scale{ spriteSize.GetX(), spriteSize.GetY(), spriteSize.GetZ() };
        D3DXMatrixTransformation(&renderingContext.m_WorldMatrix, nullptr, nullptr, &scale, nullptr, nullptr, &position);

        OK::u32 stride{ sizeof(VertexData) };
        OK::u32 offset{ 0 };

        ID3D11Buffer * const vertexBuffer = vertexList.GetVertexBuffer();
        renderingContext.m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        renderingContext.m_DeviceContext->IASetIndexBuffer(vertexList.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
        renderingContext.m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    void D3DContext::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
    {
	    projectionMatrix = m_projectionMatrix;
    }

    void D3DContext::GetWorldMatrix(D3DXMATRIX& worldMatrix)
    {
	    worldMatrix = m_worldMatrix;
    }

    void D3DContext::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
    {
	    orthoMatrix = m_orthoMatrix;
    }

    void D3DContext::GetVideoCardInfo(OK::char8* cardName, OK::s32& memory)
    {
	    strcpy_s(reinterpret_cast<char*>(cardName), 128, reinterpret_cast<char*>(m_videoCardDescription));
	    memory = m_videoCardMemory;
	    return;
    }
    
    void D3DContext::TurnZBufferOn()
    {
        m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
    }

    void D3DContext::TurnZBufferOff()
    {
        m_deviceContext->OMSetDepthStencilState(m_DepthDisabledStencilState, 1);
    }
}