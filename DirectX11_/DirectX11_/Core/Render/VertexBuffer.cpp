#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	CreateVertices();
	CreateVertexBuffer();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::SetVertexBuffer(int slot)
{
    DC->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}

void VertexBuffer::CreateVertices()
{
    Vertex_Texture temp;
    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(5, 0);
    vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 5);
    vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(5, 5);
    vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(5, 0);
    vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 0);
    vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 5);
    vertices.push_back(temp); // 오른쪽 아래

    stride = sizeof(Vertex_Texture);
    offset = 0;
}

void VertexBuffer::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex_Texture) * vertices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();

    DEVICE->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}
