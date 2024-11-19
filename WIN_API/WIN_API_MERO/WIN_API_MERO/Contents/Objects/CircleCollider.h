#pragma once
class CircleCollider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	Vector& Center() { return _center; }
	float& Radius() { return _radius; }

	void Update();
	void Render(HDC hdc);

private:
	Vector _center;
	float _radius;
};

