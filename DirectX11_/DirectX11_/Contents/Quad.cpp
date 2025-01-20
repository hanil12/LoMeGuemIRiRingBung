#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring path)
{
    CreateVertices();

	_vertexBuffer = make_shared<VertexBuffer>(vertices.data(), vertices.size(), sizeof(Vertex_Texture));

	_vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");
	_samplerState = make_shared<SamplerState>();
	_srv = make_shared<SRV>(path);
}

Quad::~Quad()
{
}

void Quad::Update()
{
}

void Quad::Render()
{
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);

    _srv->PSSet(0);
    _samplerState->PSSet(0);

    _vs->SetShader();
    _ps->SetShader();

    DC->Draw(6, 0);
}

void Quad::CreateVertices()
{
    Vertex_Texture temp;
    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    vertices.push_back(temp); // ������ �Ʒ�

    temp.pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(1, 1);
    vertices.push_back(temp); // ���� �Ʒ�

    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 0);
    vertices.push_back(temp); // ������ ��

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    vertices.push_back(temp); // ������ �Ʒ�
}
