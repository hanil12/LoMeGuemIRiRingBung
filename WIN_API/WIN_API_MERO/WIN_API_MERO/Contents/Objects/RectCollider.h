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

	void SetRed() { _curColor = 0; }
	void SetGreen() { _curColor = 1; }

private:
	int			 _curColor = 0;
	HPEN		 _colors[2];

	Vector		 _center;
	Vector		 _halfSize;
};

