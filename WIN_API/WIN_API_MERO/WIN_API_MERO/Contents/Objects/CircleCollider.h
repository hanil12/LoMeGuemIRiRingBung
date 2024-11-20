#pragma once
// 1. ��
// 2. ��Ӱ��� ����
// 3. �浹ó��(AABB, OBB)


// Collider : �浹ü
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

