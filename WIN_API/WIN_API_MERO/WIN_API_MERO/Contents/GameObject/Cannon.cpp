#include "framework.h"
#include "Barrel.h"
#include "Ball.h"

#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector(350,350), 50);
	_barrel = make_shared<Barrel>();

	// ball 생성
	for (int i = 0; i < _poolCount; i++)
	{
		auto ball = make_shared<Ball>();

		_ballPool.push_back(ball);
	}
}

Cannon::~Cannon()
{
}

// CPU
void Cannon::Update()
{
	_body->Update();
	_barrel->Update();

	for (auto ball : _ballPool)
	{
		ball->Update();
	}

	InputMove(); // 입력해서 움직이게
	InputBarrelRotation(); // 입력으로 총싱 각도 조정

	if(IsFireReady())
		Fire();
}

// GPU
void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
	for (auto ball : _ballPool)
	{
		ball->Render(hdc);
	}
}

void Cannon::Fire()
{
	// 0b 1000 0000 0000 0001
	// 0b 0111 0000 0000 0001
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		auto iter = std::find_if(_ballPool.begin(), _ballPool.end(), [](const shared_ptr<Ball>& ball) -> bool 
		{
			if(ball->IsActive() == false)
				return true;
			return false;
		});

		if(iter == _ballPool.end()) return;

		(*iter)->Fire(_barrel->GetMuzzle(), _barrel->GetDirection());
	}
}

void Cannon::InputMove()
{
	if(GetAsyncKeyState(VK_LEFT) & 0x8001)
		_body->Center().x -= 3;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		_body->Center().x += 3;
}

void Cannon::InputBarrelRotation()
{
	Vector dir = mousePos - _body->Center();
	dir.Normalize();

	_barrel->SetDirection(dir);
}
