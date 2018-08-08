#pragma once

/*****************************************/
/* This class was largely copied from:   */
/* http://www.rastertek.com/tutdx11.html */
/*****************************************/

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

namespace OK
{
    class ModelComponent;
    class TransformComponent;
    struct RenderingContext;
    struct VertexList;

    class D3DContext
    {
    public:
        D3DContext();
        ~D3DContext();

        bool Initialize(OK::s32, OK::s32, OK::Bool, HWND, OK::Bool, OK::f32, OK::f32);
        void Shutdown();

        void BeginScene(OK::f32, OK::f32, OK::f32, OK::f32);
        void EndScene();

        ID3D11Device* GetDevice();
        ID3D11DeviceContext* GetDeviceContext();

        void ComputeRenderingContext(RenderingContext& renderingContext, const TransformComponent* cameraTransform);
        void PrepareModelRendering(RenderingContext& renderingContext, VertexList& vertexList);

        void GetProjectionMatrix(D3DXMATRIX&);
        void GetWorldMatrix(D3DXMATRIX&);
        void GetOrthoMatrix(D3DXMATRIX&);

        void GetVideoCardInfo(OK::char8*, OK::s32&);

    private:
        OK::Bool m_vsync_enabled;
        OK::s32 m_videoCardMemory;
        OK::char8 m_videoCardDescription[128];
        IDXGISwapChain* m_swapChain;
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_deviceContext;
        ID3D11RenderTargetView* m_renderTargetView;
        ID3D11Texture2D* m_depthStencilBuffer;
        ID3D11DepthStencilState* m_depthStencilState;
        ID3D11DepthStencilView* m_depthStencilView;
        ID3D11RasterizerState* m_rasterState;
        D3DXMATRIX m_projectionMatrix;
        D3DXMATRIX m_worldMatrix;
        D3DXMATRIX m_orthoMatrix;
    };
}