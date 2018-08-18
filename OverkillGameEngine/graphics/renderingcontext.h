#pragma once

#include <core\math\vectors.h>

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

namespace OK
{
    struct RenderingContext : public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
        ID3D11DeviceContext* m_DeviceContext = nullptr;
        ID3D11Device* m_Device = nullptr;
        D3DXMATRIX m_ProjectionMatrix;
        D3DXMATRIX m_WorldMatrix;
        D3DXMATRIX m_ViewMatrix;

        OK::Vec4 m_CameraPosition;

        OK::Vec4 m_AmbientLightColor{ 1.0f , 1.0f , 1.0f , 1.0f };
        OK::Vec4 m_DiffuseLightColor{ 1.0f , 1.0f , 1.0f , 1.0f };
        OK::Vec4 m_SpecularLightColor{ 1.0f , 1.0f , 1.0f , 1.0f };
        OK::Vec4 m_LightDirection{ 0.0f, 0.0f, -1.0f};
        OK::f32 m_SpecularLightPower;
    };
}