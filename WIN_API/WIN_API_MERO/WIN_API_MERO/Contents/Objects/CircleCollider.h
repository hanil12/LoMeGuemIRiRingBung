#pragma once
// 1. 색
// 2. 상속관계 정의
// 3. 충돌처리(AABB, OBB)


// Collider : 충돌체
class CircleCollider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	Vector& Center() { return _center; }
	float& Radius() { return _radius; }

	void Update();
	void Render(HDC hdc);

	void SetRed() { _curColor = 0; }
	void SetGreen() { _curColor = 1; }

private:
	int			 _curColor = 0;
	HPEN		 _colors[2];

	Vector		 _center;
	float		 _radius;
};

