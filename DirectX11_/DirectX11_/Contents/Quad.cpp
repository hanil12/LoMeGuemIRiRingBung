#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring path)
{
    CreateVertices();

	_vertexBuffer = make_shared<VertexBuffer>(vertices.data(), vertices.size(), sizeof(Vertex_Texture));

	_vs = make_shared<VertexShader>(L"Shader/TextureVertexShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TexturePixelShader.hlsl");
	_samplerState = make_shared<SamplerState>();
	_srv = make_shared<SRV>(path);

    _pos = {WIN_WIDTH * 0.5f,WIN_HEIGHT * 0.5f};
    _scale = {0.3f,0.3f};
    _angle = 0.0f;
    _world = make_shared<MatrixBuffer>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _angle += 0.001f;

    XMMATRIX S = XMMatrixScaling(_scale.x, _scale.y, 1);
    XMMATRIX R = XMMatrixRotationZ(_angle);
    XMMATRIX T = XMMatrixTranslation(_pos.x, _pos.y, 0);

    XMMATRIX srtMaxtrix = S * R * T;

    _world->SetData(srtMaxtrix);
    _world->Update();
}

void Quad::Render()
{
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);

    _srv->PSSet(0);
    _samplerState->PSSet(0);

    _world->SetVSBuffer(0);

    _vs->SetShader();
    _ps->SetShader();

    DC->Draw(6, 0);
}

void Quad::CreateVertices()
{
    Vertex_Texture temp;
    temp.pos = XMFLOAT3(-300.0f, 300.0f, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(300.0f, -300.0f, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-300.0f, -300.0f, 0.0f);
    temp.uv = XMFLOAT2(1, 1);
    vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-300.0f, 300.0f, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(300.0f, 300.0f, 0.0f);
    temp.uv = XMFLOAT2(0, 0);
    vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(300.0f, -300.0f, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    vertices.push_back(temp); // 오른쪽 아래
}
