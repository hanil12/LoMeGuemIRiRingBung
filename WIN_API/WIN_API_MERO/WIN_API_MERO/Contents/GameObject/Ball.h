#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

private:
	shared_ptr<CircleCollider> _ball;
	Vector _direction = Vector(1,0);
	float _speed = 30.0f;;
};

