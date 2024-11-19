#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
: _center(center)
, _halfSize(size * 0.5f)
{
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
	// TODO... ���콺 ��ġ�� ��������.
}

void RectCollider::Render(HDC hdc)
{
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
