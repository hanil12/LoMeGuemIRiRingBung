#pragma once
class RectCollider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider();

	Vector& Center() { return _center; }

	int Left() { return _center.x - _halfSize.x; }
	int Right() { return _center.x + _halfSize.x; }
	int Top() { return _center.y - _halfSize.y; }
	int Bottom() { return _center.y + _halfSize.y; }

	void Update();
	void Render(HDC hdc);

private:
	Vector _center;
	Vector _halfSize;
};

