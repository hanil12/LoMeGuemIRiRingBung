#include "framework.h"
#include "Barrel.h"

#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector(350,350), 50);
	_barrel = make_shared<Barrel>();
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	InputMove(); // �Է��ؼ� �����̰�
	InputBarrelRotation(); // �Է����� �ѽ� ���� ����

	_body->Update();
	_barrel->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
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
	// TODO : ����Ű ���� ������ �ѽ��� ������ +�� �ǰ�
	// ����Ű �Ʒ��� ������ �ѽ��� ������ -�� �ǰ��ϱ�.

	Vector dir = mousePos - _body->Center();
	dir.Normalize();

	//_barrel->_start = _body->Center();
	//_barrel->_end = _body->Center() + dir * _barrelLength;
}
