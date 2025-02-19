#include "framework.h"
#include "RectCollider.h"
#include "CircleCollider.h"

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

float RectCollider::SeperateAxis(Vector unit, Vector a, Vector b)
{
    float r1 = abs(unit.Dot(a));
    float r2 = abs(unit.Dot(b));

    return r1 + r2;
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

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    OBB_DESC desc = GetOBB();

    Vector aTob = other->Center() - desc.position;
    float radius = other->Radius();

    // 대각 예외처리
    float maxLength = sqrtf(desc.length[0] * desc.length[0] + desc.length[1] * desc.length[1]);
    if(maxLength + radius < aTob.Length())
        return false;

    Vector uea1 = desc.direction[0];
    float distance_ea1 = abs(uea1.Dot(aTob));
    if(desc.length[0] + radius < distance_ea1)
        return false;

    Vector uea2 = desc.direction[1];
    float distance_ea2 = abs(uea2.Dot(aTob));
    if(desc.length[1] + radius < distance_ea2)
        return false;

    return true;
}


bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    OBB_DESC desc1 = GetOBB();
    OBB_DESC desc2 = other->GetOBB();

    Vector aTob = desc2.position - desc1.position;

    // A 정보
    Vector uea1 = desc1.direction[0];
    Vector ea1 = uea1 * desc1.length[0];
    Vector uea2 = desc1.direction[1];
    Vector ea2 = uea2 * desc1.length[1];
    // B 정보
    Vector ueb1 = desc2.direction[0];
    Vector eb1 = ueb1 * desc2.length[0];
    Vector ueb2 = desc2.direction[1];
    Vector eb2 = ueb2 * desc2.length[1];

    float lengthA = ea1.Length();
    float lengthB = SeperateAxis(uea1, eb1, eb2);
    float distance = abs(uea1.Dot(aTob));
    if(distance > lengthA + lengthB)
        return false;

    lengthA = ea2.Length();
    lengthB = SeperateAxis(uea2, eb1, eb2);
    distance = abs(uea2.Dot(aTob));
    if (distance > lengthA + lengthB)
        return false;

    lengthA = SeperateAxis(ueb1, ea1, ea2);
    lengthB = eb1.Length();
    distance = abs(ueb1.Dot(aTob));
    if (distance > lengthA + lengthB)
        return false;

    lengthA = SeperateAxis(ueb2, ea1, ea2);
    lengthB = eb2.Length();
    distance = abs(ueb2.Dot(aTob));
    if (distance > lengthA + lengthB)
        return false;

    return true;
}

int RectCollider::Block(shared_ptr<RectCollider> other)
{
    if(IsCollision(other) == false)
        return -1;

    OBB_DESC desc1 = GetOBB();
    OBB_DESC desc2 = other->GetOBB();

    Vector gap;
    gap.x = (desc1.length[0] + desc2.length[0]) - abs(desc1.position.x - desc2.position.x) + 0.0001f;
    gap.y = (desc1.length[1] + desc2.length[1]) - abs(desc1.position.y - desc2.position.y) + 0.0001f;

    // 상속된 Collider에 Block X

    // gap의 y의 값이 더 작으면 y축으로 밀어준다.
    if (gap.x > gap.y)
    {
        if (desc2.position.y < desc1.position.y)
        {
            other->GetTransform()->SetLocalLocation(desc2.position + Vector(0, -gap.y));
            return 0;
        }
        else
        {
            other->GetTransform()->SetLocalLocation(desc2.position + Vector(0, +gap.y));
            // 위로 부딫힐 경우 1
            return 1;
        }
    }

    // gap의 x 값이 더 작음
    if(desc2.position.x < desc1.position.x)
        other->GetTransform()->AddLocalLocation(Vector(-gap.x, 0));
    else
        other->GetTransform()->AddLocalLocation(Vector(gap.x, 0));

    return 0;
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
