#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_fixedCircle = make_shared<RectCollider>(Vector(400,400), Vector(300,120));
	_movableCircle = make_shared<RectCollider>(Vector(0,0), Vector(100,100));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_fixedCircle->Update();
	_movableCircle->Update();

	// 점충돌
	//if (_fixedCircle->IsCollision(mousePos))
	//	_fixedCircle->SetRed();
	//else
	//	_fixedCircle->SetGreen();

	_movableCircle->Center() = mousePos;

	// 원, 원 충돌
	if (_fixedCircle->IsCollision(_movableCircle))
		_fixedCircle->SetRed();
	else
		_fixedCircle->SetGreen();
}

void CollisionScene::Render(HDC hdc)
{
	_fixedCircle->Render(hdc);
	_movableCircle->Render(hdc);
}
