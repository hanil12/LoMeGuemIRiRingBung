#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float radius)
: _center(center)
, _radius(radius)
{
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

	Ellipse(hdc,left, top, right, bottom);
}
