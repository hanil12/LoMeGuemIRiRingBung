#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
: _halfSize(size * 0.5f)
{
	CreateVertices();

    _vertexBuffer = 
        make_shared<VertexBuffer>(_vertices.data(), _vertices.size(), sizeof(Vertex));

    _vs = make_shared<VertexShader>(L"Shader/ColliderVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPixelShader.hlsl");

    _transform = make_shared<Transform>();
    _transform->SetLocalLocation(center);

    _colorBuffer = make_shared<ColorBuffer>();
    _colorBuffer->SetData(XMFLOAT4(0,1,0,1));
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
    _colorBuffer->Update();
}

void RectCollider::Render()
{
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);

    _transform->SetVSSlot(0);
    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->SetShader();
    _ps->SetShader();

    DC->Draw(_vertices.size(),0);
}

RectCollider::OBB_DESC RectCollider::GetOBB()
{
    OBB_DESC result;
    result.position = _transform->GetWorldLocation();
    result.length[0] = _halfSize.x * _transform->GetWorldScale().x;
    result.length[1] = _halfSize.y * _transform->GetWorldScale().y;

    auto matrix = _transform->GetMatrix();
    result.direction[0] = {matrix.r[0].m128_f32[0], matrix.r[0].m128_f32[1] };
    result.direction[1] = {matrix.r[1].m128_f32[0], matrix.r[1].m128_f32[1] };
    result.direction[0].Normalize();
    result.direction[1].Normalize();

    return result;
}

bool RectCollider::IsCollision(const Vector& pos)
{
    // 각 축으로 내적 후 비교

    OBB_DESC desc = GetOBB();

    Vector aTob = pos - desc.position;

    Vector uea1 = desc.direction[0];
    Vector ea1 = desc.direction[0] * desc.length[0];

    float distance_ea1 = abs(uea1.Dot(aTob));
    if(distance_ea1 > ea1.Length())
        return false;

    Vector uea2 = desc.direction[1];
    Vector ea2 = desc.direction[1] * desc.length[1];

    float distance_ea2 = abs(uea2.Dot(aTob));
    if (distance_ea2 > ea2.Length())
        return false;

    return true;
}

void RectCollider::CreateVertices()
{
    Vertex temp;
    temp.pos = XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위
}
