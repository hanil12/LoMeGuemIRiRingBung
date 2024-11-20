#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
: _center(center)
, _halfSize(size * 0.5f)
{
	_colors[0] = CreatePen(3, 3, RED);
	_colors[1] = CreatePen(3, 3, GREEN);
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
	SelectObject(hdc, _colors[_curColor]);

	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
