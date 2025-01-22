#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
    _pos = { 0.0f,0.0f };
    _scale = { 1.0f, 1.0f };
    _angle = 0.0f;
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

    XMMATRIX srtMaxtrix = S * R * T;

    _world->SetData(srtMaxtrix);
    _world->Update();
}

void Transform::SetVSSlot(int slot)
{
    _world->SetVSBuffer(slot);
}
