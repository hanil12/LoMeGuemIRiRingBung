#include "framework.h"
#include "RectCollider.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float radius)
: _center(center)
, _radius(radius)
{
	_colors[0] = CreatePen(3,3,RED);
	_colors[1] = CreatePen(3,3,GREEN);

	SetGreen();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	// TODO
}

void CircleCollider::Render(HDC hdc)
{
	int left = _center.x - _radius;
	int right = _center.x + _radius;
	int top  = _center.y - _radius;
	int bottom = _center.y + _radius;

	SelectObject(hdc, _colors[_curColor]);

	Ellipse(hdc,left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector& pos) const
{
	float length = (pos - _center).Length();

	return length < _radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other) const
{
	return false;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other) const
{
	return false;
}
