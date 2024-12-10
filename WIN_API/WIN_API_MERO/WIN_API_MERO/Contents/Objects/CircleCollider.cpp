#include "framework.h"
#include "RectCollider.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector center, float radius)
: _radius(radius)
{
	_type = Collider::Type::CIRCLE;

	_center = center;
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

	if (_curColor != 2)
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
	float radiusSum = _radius + other->Radius();
	float length = (other->Center() - _center).Length();

	return length < radiusSum;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other) const
{
	return other->IsCollision(static_pointer_cast<CircleCollider>(const_pointer_cast<Collider>(shared_from_this())));
}
