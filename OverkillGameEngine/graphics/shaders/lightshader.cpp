#include <stdafx.h>
#include <graphics\shaders\lightshader.h>

#include <core\math\vectors.h>
#include <graphics\renderingcontext.h>
#include <graphics\texture\texture.h>
#include <d3dx11async.h>

namespace OK
{
    LightShader::LightShader(const OK::char8* shaderName)
        : Shader{ shaderName }
        , m_SampleState{ nullptr }
        , m_LightBuffer{ nullptr }
    {
    }

    void LightShader::InitializeShader(const RenderingContext& renderingContext, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile)
    {
        HRESULT result;
        ID3D10Blob* errorMessage{ nullptr };
        ID3D10Blob* vertexShaderBuffer{ nullptr };
        ID3D10Blob* pixelShaderBuffer{ nullptr };
        D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
        OK::u32 numElements;
        D3D11_SAMPLER_DESC samplerDesc;
        D3D11_BUFFER_DESC matrixBufferDesc;
        D3D11_BUFFER_DESC lightBufferDesc;

        result = D3DX11CompileFromFile(vertexShaderFile, nullptr, nullptr, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr, &vertexShaderBuffer, &errorMessage, NULL);
        okAssert(SUCCEEDED(result), "Failed to compile Vertex shader.");
        result = D3DX11CompileFromFile(pixelShaderFile, nullptr, nullptr, "LightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, nullptr, &pixelShaderBuffer, &errorMessage, NULL);
        okAssert(SUCCEEDED(result), "Failed to compile Pixel shader.");
        result = renderingContext.m_Device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_VertexShader);
        okAssert(SUCCEEDED(result), "Failed to create the vertex shader from the buffer.");
        result = renderingContext.m_Device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_PixelShader);
        okAssert(SUCCEEDED(result), "Failed to create the pixel shader from the buffer.");

        polygonLayout[0].SemanticName = "POSITION";
        polygonLayout[0].SemanticIndex = 0;
        polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        polygonLayout[0].InputSlot = 0;
        polygonLayout[0].AlignedByteOffset = 0;
        polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[0].InstanceDataStepRate = 0;

        polygonLayout[1].SemanticName = "TEXCOORD";
        polygonLayout[1].SemanticIndex = 0;
        polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
        polygonLayout[1].InputSlot = 0;
        polygonLayout[1].AlignedByteOffset = (2 * sizeof(OK::Vec4));
        polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[1].InstanceDataStepRate = 0;

        polygonLayout[2].SemanticName = "NORMAL";
        polygonLayout[2].SemanticIndex = 0;
        polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        polygonLayout[2].InputSlot = 0;
        polygonLayout[2].AlignedByteOffset = (3 * sizeof(OK::Vec4));
        polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[2].InstanceDataStepRate = 0;

        numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

        result = renderingContext.m_Device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout);
        okAssert(SUCCEEDED(result), "Failed to create vertex input layout.");

        vertexShaderBuffer->Release();
        vertexShaderBuffer = nullptr;
        pixelShaderBuffer->Release();
        pixelShaderBuffer = nullptr;

        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0] = 0;
        samplerDesc.BorderColor[1] = 0;
        samplerDesc.BorderColor[2] = 0;
        samplerDesc.BorderColor[3] = 0;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
        result = renderingContext.m_Device->CreateSamplerState(&samplerDesc, &m_SampleState);
        okAssert(SUCCEEDED(result), "Failed to create sample state.");

        matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        matrixBufferDesc.ByteWidth = sizeof(MatrixBufferData);
        matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        matrixBufferDesc.MiscFlags = 0;
        matrixBufferDesc.StructureByteStride = 0;
        result = renderingContext.m_Device->CreateBuffer(&matrixBufferDesc, nullptr, &m_MatrixBuffer);
        okAssert(SUCCEEDED(result), "Failed to create Matrix.");

        lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        lightBufferDesc.ByteWidth = sizeof(LightBufferData);
        lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        lightBufferDesc.MiscFlags = 0;
        lightBufferDesc.StructureByteStride = 0;
        result = renderingContext.m_Device->CreateBuffer(&lightBufferDesc, nullptr, &m_LightBuffer);
        okAssert(SUCCEEDED(result), "Failed to create light buffer.");
    }

    void LightShader::ShutdownShader()
    {
        Shader::ShutdownShader();
        if (m_SampleState != nullptr)
        {
            m_SampleState->Release();
            m_SampleState = nullptr;
        }
        if (m_LightBuffer != nullptr)
        {
            m_LightBuffer->Release();
            m_LightBuffer = nullptr;
        }
    }

    void LightShader::SetShaderParameters(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData)
    {
        HRESULT result;
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        unsigned int bufferNumber;
        MatrixBufferData* dataPtr;
        LightBufferData* dataPtr2;

        result = renderingContext.m_DeviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        okAssert(SUCCEEDED(result), "Failed to lock the constant buffer.");

        dataPtr = reinterpret_cast<MatrixBufferData*>(mappedResource.pData);
        D3DXMatrixTranspose(&dataPtr->world, &renderingContext.m_WorldMatrix);
        D3DXMatrixTranspose(&dataPtr->view, &renderingContext.m_ViewMatrix);
        D3DXMatrixTranspose(&dataPtr->projection, &renderingContext.m_ProjectionMatrix);

        renderingContext.m_DeviceContext->Unmap(m_MatrixBuffer, 0);
        bufferNumber = 0;

        ID3D11ShaderResourceView* const texture{ shaderRenderData.m_Texture->GetTexture() };
        renderingContext.m_DeviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
        renderingContext.m_DeviceContext->PSSetShaderResources(0, 1, &texture);


        result = renderingContext.m_DeviceContext->Map(m_LightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        okAssert(SUCCEEDED(result), "Failed to lock the light constant buffer.");

        dataPtr2 = (LightBufferData*)mappedResource.pData;
        dataPtr2->m_AmbientColor = renderingContext.m_AmbientLightColor;
        dataPtr2->m_DiffuseColor = renderingContext.m_DiffuseLightColor;
        dataPtr2->m_LightDirection = renderingContext.m_LightDirection;

        renderingContext.m_DeviceContext->Unmap(m_LightBuffer, 0);
        bufferNumber = 0;

        renderingContext.m_DeviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_LightBuffer);

    }

    void LightShader::RenderShaderInternal(const RenderingContext& renderingContext, const ShaderRenderData& shaderRenderData)
    {
        renderingContext.m_DeviceContext->IASetInputLayout(m_Layout);
        renderingContext.m_DeviceContext->VSSetShader(m_VertexShader, nullptr, 0);
        renderingContext.m_DeviceContext->PSSetShader(m_PixelShader, nullptr, 0);
        renderingContext.m_DeviceContext->PSSetSamplers(0, 1, &m_SampleState);
        renderingContext.m_DeviceContext->DrawIndexed(shaderRenderData.m_IndexCount, 0, 0);
    }
}