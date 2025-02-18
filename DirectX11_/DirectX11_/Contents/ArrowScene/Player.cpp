#include "framework.h"
#include "Player.h"

Player::Player()
{
	_quad = make_shared<Quad>(L"Resource/Player.png");
	_body = make_shared<RectCollider>(CENTER, _quad->ImageSize());
	
	_quad->GetTransform()->SetParent(_body->GetTransform());

	_body->GetTransform()->SetScale(0.1f);
}

Player::~Player()
{
}

void Player::PreUpdate()
{
	_body->Update();
}

void Player::Update()
{
	Input();

	_quad->Update();
}

void Player::Render()
{
	_quad->Render();
}

void Player::PostRender()
{
	_body->Render();
}

void Player::Input()
{
	if (KEY_PRESS('A'))
	{
		_body->GetTransform()->AddLocalLocation(Vector(-1,0) * DELTA_TIME * _speed);
		_quad->SetFlipX(1);
	}

	if (KEY_PRESS('D'))
	{
		_body->GetTransform()->AddLocalLocation(Vector(1,0) * DELTA_TIME * _speed);
		_quad->SetFlipX(0);
	}
}
