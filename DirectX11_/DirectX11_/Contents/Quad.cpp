#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring path)
{
	_vs = make_shared<VertexShader>(L"Shader/TextureVertexShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TexturePixelShader.hlsl");
	_srvPath = path;
    ADD_SRV(_srvPath);

    CreateVertices();

    _transform = make_shared<Transform>();
    _flipBuffer = make_shared<FlipBuffer>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->Update();
}

void Quad::Render()
{
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);
    _indexBuffer->IASetIndexBuffer();

    ADD_SRV(_srvPath)->PSSet(0);
    SAMPLER->PSSet(0);

    _transform->SetVSSlot(0);
    _flipBuffer->SetPSBuffer(0);

    _vs->SetShader();
    _ps->SetShader();

    DC->DrawIndexed(_indices.size(), 0,0);
}

Vector Quad::ImageSize()
{
    return ADD_SRV(_srvPath)->GetSize();
}

void Quad::CreateVertices()
{
    Vector halfSize = ADD_SRV(_srvPath)->GetSize() * 0.5f;

    Vertex_Texture temp;
    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(0, 0);
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(1, 1);
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    _vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    _vertices.push_back(temp); // 오른쪽 위

    // 031 012
    _indices.push_back(0);
    _indices.push_back(3);
    _indices.push_back(1);
    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), _vertices.size(), sizeof(Vertex_Texture));
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}
