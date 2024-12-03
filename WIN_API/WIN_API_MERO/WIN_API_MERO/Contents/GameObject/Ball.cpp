#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_ball = make_shared<CircleCollider>(Vector(0,0), 10);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if(IsOut() == true) _isActive = false;
	if(_isActive == false)	return;

	_ball->Update();

	// 투사제(Projectile)
	// 어디서부터 어느 방향(_direction)으로 어떤 속도(_speed)로 날아간다.
	_ball->Center() += _direction * _speed;

	_gravity += 1.0f;
	_ball->Center().y += _gravity;
}

void Ball::Render(HDC hdc)
{
	if(_isActive == false) return;

	_ball->Render(hdc);
}

void Ball::Fire(Vector pos, Vector dir)
{
	_isActive = true;
	_gravity = 0.0f;

	SetPos(pos);
	SetDirection(dir);
}

bool Ball::IsOut()
{
	int x = _ball->Center().x;
	int y = _ball->Center().y;

	if(x > WIN_WIDTH || x < 0 || y > WIN_HEIGHT)
		return true;

	return false;
}
