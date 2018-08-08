#include <stdafx.h>
#include <graphics\shaders\shader.h>

#include <graphics\renderingcontext.h>
#include <d3dx11async.h>

namespace OK
{
    Shader::Shader(const RenderingContext& renderingContext, const OK::char8* shaderName, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile)
        : m_Name{ shaderName }
    {
        InitializeShader(renderingContext, vertexShaderFile, pixelShaderFile);
    }

    Shader::~Shader()
    {
        ShutdownShader();
    }

    void Shader::RunShader(const RenderingContext& renderingContext, OK::u32 indexCount)
    {
        SetShaderParameters(renderingContext);
        RenderShaderInternal(renderingContext, indexCount);
    }

    void Shader::InitializeShader(const RenderingContext& renderingContext, const OK::char8* vertexShaderFile, const OK::char8* pixelShaderFile)
    {
        HRESULT result;
        ID3D10Blob* errorMessage;
        ID3D10Blob* vertexShaderBuffer;
        ID3D10Blob* pixelShaderBuffer;
        D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
        OK::u32 numElements;
        D3D11_BUFFER_DESC matrixBufferDesc;

        errorMessage = nullptr;
        vertexShaderBuffer = nullptr;
        pixelShaderBuffer = nullptr;

        result = D3DX11CompileFromFile(vertexShaderFile, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
        okAssert(SUCCEEDED(result), "Failed to compile Vertex shader.");

        result = D3DX11CompileFromFile(pixelShaderFile, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
        okAssert(SUCCEEDED(result), "Failed to compile Pixel shader.");

        result = renderingContext.m_Device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_VertexShader);
        okAssert(SUCCEEDED(result), "Failed to create the vertex shader from the buffer.");

        result = renderingContext.m_Device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_PixelShader);
        okAssert(SUCCEEDED(result), "Failed to create the pixel shader from the buffer.");

        polygonLayout[0].SemanticName = "POSITION";
        polygonLayout[0].SemanticIndex = 0;
        polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        polygonLayout[0].InputSlot = 0;
        polygonLayout[0].AlignedByteOffset = 0;
        polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[0].InstanceDataStepRate = 0;

        polygonLayout[1].SemanticName = "COLOR";
        polygonLayout[1].SemanticIndex = 0;
        polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        polygonLayout[1].InputSlot = 0;
        polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[1].InstanceDataStepRate = 0;

        numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

        result = renderingContext.m_Device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_Layout);
        okAssert(SUCCEEDED(result), "Failed to create the vertex input layout.");

        // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
        vertexShaderBuffer->Release();
        vertexShaderBuffer = 0;

        pixelShaderBuffer->Release();
        pixelShaderBuffer = 0;

        matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        matrixBufferDesc.ByteWidth = sizeof(MatrixBufferData);
        matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        matrixBufferDesc.MiscFlags = 0;
        matrixBufferDesc.StructureByteStride = 0;

        result = renderingContext.m_Device->CreateBuffer(&matrixBufferDesc, NULL, &m_MatrixBuffer);
        okAssert(SUCCEEDED(result), "Failed to create matrix buffer.");
    }


    void Shader::ShutdownShader()
    {
        if (m_MatrixBuffer)
        {
            m_MatrixBuffer->Release();
            m_MatrixBuffer = nullptr;
        }
        if (m_Layout)
        {
            m_Layout->Release();
            m_Layout = nullptr;
        }
        if (m_PixelShader)
        {
            m_PixelShader->Release();
            m_PixelShader = nullptr;
        }
        if (m_VertexShader)
        {
            m_VertexShader->Release();
            m_VertexShader = nullptr;
        }
    }

    void Shader::SetShaderParameters(const RenderingContext& renderingContext)
    {
        HRESULT result;
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        MatrixBufferData* dataPtr;
        OK::u32 bufferNumber;

        result = renderingContext.m_DeviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        okAssert(SUCCEEDED(result), "Failed to lock the constant buffer.");

        dataPtr = reinterpret_cast<MatrixBufferData*>(mappedResource.pData);
        D3DXMatrixTranspose(&dataPtr->world, &renderingContext.m_WorldMatrix);
        D3DXMatrixTranspose(&dataPtr->view, &renderingContext.m_ViewMatrix);
        D3DXMatrixTranspose(&dataPtr->projection, &renderingContext.m_ProjectionMatrix);

        renderingContext.m_DeviceContext->Unmap(m_MatrixBuffer, 0);
        bufferNumber = 0;
        renderingContext.m_DeviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
    }


    void Shader::RenderShaderInternal(const RenderingContext& renderingContext, OK::s32 indexCount)
    {
        ID3D11DeviceContext* deviceContext{ renderingContext.m_DeviceContext };
        deviceContext->IASetInputLayout(m_Layout);
        deviceContext->VSSetShader(m_VertexShader, NULL, 0);
        deviceContext->PSSetShader(m_PixelShader, NULL, 0);
        deviceContext->DrawIndexed(indexCount, 0, 0);
    }
}