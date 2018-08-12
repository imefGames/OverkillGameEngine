#pragma once

#include <core\math\vectors.h>

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

        OK::Vec4 m_LightColor{ 1.0f , 1.0f , 1.0f , 1.0f };
        OK::Vec4 m_LightDirection{ 0.0f, 0.0f, -1.0f};

        static void* operator new(size_t size);
        static void* operator new[](size_t size);
        static void operator delete(void* pointer);
        static void operator delete[](void* pointer);
    };
}