#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float radius)
: _radius(radius)
{
    CreateVertices();

    _vertexBuffer =
        make_shared<VertexBuffer>(_vertices.data(), _vertices.size(), sizeof(Vertex));

    _vs = make_shared<VertexShader>(L"Shader/ColliderVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPixelShader.hlsl");

    _transform = make_shared<Transform>();
    _transform->SetLocalLocation(center);

    _colorBuffer = make_shared<ColorBuffer>();
    _colorBuffer->SetData(XMFLOAT4(0, 1, 0, 1));
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    _transform->Update();
    _colorBuffer->Update();
}

void CircleCollider::Render()
{
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);

    _transform->SetVSSlot(0);
    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->SetShader();
    _ps->SetShader();

    DC->Draw(_vertices.size(), 0);
}

bool CircleCollider::IsCollision(const Vector& pos)
{
    float length = (pos - Center()).Length();

    return length < Radius();
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    float length = (other->Center() - Center()).Length();

    return length < other->Radius() + Radius();
}

void CircleCollider::CreateVertices()
{
    float theta = 2 * PI / 30.0f;
 
    for (int i = 0; i < 31; i++)
    {
        Vertex temp;
        temp.pos.x = cos(theta * i) * _radius;
        temp.pos.y = sin(theta * i) * _radius;
        temp.pos.z = 0.0f;

        _vertices.push_back(temp);
    }
}
