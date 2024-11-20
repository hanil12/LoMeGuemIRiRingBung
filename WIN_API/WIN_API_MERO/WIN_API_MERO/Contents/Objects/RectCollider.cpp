#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector center, Vector size)
: _halfSize(size * 0.5f)
{
	_center = center;

	_colors[0] = CreatePen(3, 3, RED);
	_colors[1] = CreatePen(3, 3, GREEN);
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
	// TODO... 마우스 위치로 움직여라.
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _colors[_curColor]);

	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}

bool RectCollider::IsCollision(const Vector& pos) const
{
	return false;
}

bool RectCollider::IsCollision(shared_ptr<class CircleCollider> other) const
{
	return false;
}

bool RectCollider::IsCollision(shared_ptr<class RectCollider> other) const
{
	return false;
}
