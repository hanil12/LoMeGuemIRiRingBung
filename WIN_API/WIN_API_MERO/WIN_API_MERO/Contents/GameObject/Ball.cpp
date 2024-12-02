#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_ball = make_shared<CircleCollider>(Vector(-1000,0), 15);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	_ball->Update();

	// 투사제(Projectile)
	// 어디서부터 어느 방향(_direction)으로 어떤 속도(_speed)로 날아간다.
	_ball->Center() += _direction * _speed;
}

void Ball::Render(HDC hdc)
{
	_ball->Render(hdc);
}
