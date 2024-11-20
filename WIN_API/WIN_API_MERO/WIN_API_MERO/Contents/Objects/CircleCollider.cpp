#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float radius)
: _center(center)
, _radius(radius)
{
	_colors[0] = CreatePen(3,3,RED);
	_colors[1] = CreatePen(3,3,GREEN);
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
