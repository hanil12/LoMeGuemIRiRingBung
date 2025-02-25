#include "framework.h"
#include "Sprite.h"

#include "Action.h"

Sprite::Sprite(wstring path, Vector maxFrame)
: Quad(path)
{
	_ps = make_shared<PixelShader>(L"Shader/SpritePixelShader.hlsl");
	_frameBuffer = make_shared<FrameBuffer>();
	_frameBuffer->SetMaxFrame(maxFrame);
	SetCurFrame(Vector(0,0));

    CreateVertices();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	Quad::Update();
}

void Sprite::Render()
{
	_frameBuffer->SetPSBuffer(1);
	Quad::Render();
}

void Sprite::SetCurFrame(Vector frame)
{
	_frameBuffer->SetCurFrame(frame);
	_frameBuffer->Update();
}

void Sprite::SetCurFrame(Action::Clip clip)
{
    Vector clipSize = clip.size;
    XMFLOAT2 frame;
    frame.x = clip.startPos.x / clipSize.x;
    frame.y = clip.startPos.y / clipSize.y;

    _frameBuffer->SetCurFrame(frame);
    _frameBuffer->Update();
}

void Sprite::CreateVertices()
{
    _indices.clear();
    _vertices.clear();

    Vector halfSize = ADD_SRV(_srvPath)->GetSize() * 0.5f;
    halfSize.x *= (1 / MaxFrame().x);
    halfSize.y *= (1 / MaxFrame().y);

    Vertex_Texture temp;
    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(0, 0);
    _vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(1, 1);
    _vertices.push_back(temp); // ������ �Ʒ�

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(0, 1);
    _vertices.push_back(temp); // ���� �Ʒ�

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    temp.uv = XMFLOAT2(1, 0);
    _vertices.push_back(temp); // ������ ��

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
