#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

namespace OK
{
    struct RenderingContext
    {
        ID3D11DeviceContext* m_DeviceContext = nullptr;
        ID3D11Device* m_Device = nullptr;
        D3DXMATRIX m_ProjectionMatrix;
        D3DXMATRIX m_WorldMatrix;
        D3DXMATRIX m_ViewMatrix;
    };
}