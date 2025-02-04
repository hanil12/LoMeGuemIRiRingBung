#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
    _pos = { 0.0f,0.0f };
    _scale = { 1.0f, 1.0f };
    _angle = 0.0f;
    _srtMatrix = XMMatrixIdentity();

    _world = make_shared<MatrixBuffer>();
}

Transform::~Transform()
{
}

void Transform::Update()
{
    XMMATRIX S = XMMatrixScaling(_scale.x, _scale.y, 1);
    XMMATRIX R = XMMatrixRotationZ(_angle);
    XMMATRIX T = XMMatrixTranslation(_pos.x, _pos.y, 0);

    _srtMatrix = S * R * T;

    if (_parent.expired() == false)
    {
        _srtMatrix *= _parent.lock()->GetMatrix();
    }

    _world->SetData(_srtMatrix);
    _world->Update();
}

void Transform::SetVSSlot(int slot)
{
    _world->SetVSBuffer(slot);
}

Vector Transform::GetWorldLocation()
{
    float x = _srtMatrix.r[3].m128_f32[0];
    float y = _srtMatrix.r[3].m128_f32[1];

    return Vector(x,y);
}
