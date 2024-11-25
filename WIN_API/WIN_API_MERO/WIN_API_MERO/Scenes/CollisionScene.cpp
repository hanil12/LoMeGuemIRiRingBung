#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_fixedCircle = make_shared<CircleCollider>(Vector(400,400), 70);
	_movableRect = make_shared<RectCollider>(Vector(0,0), Vector(100,100));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_fixedCircle->Update();
	_movableRect->Update();

	// 점충돌
	//if (_fixedCircle->IsCollision(mousePos))
	//	_fixedCircle->SetRed();
	//else
	//	_fixedCircle->SetGreen();

	_movableRect->Center() = mousePos;

	// 원, 원 충돌
	if (_movableRect->IsCollision(_fixedCircle))
		_fixedCircle->SetRed();
	else
		_fixedCircle->SetGreen();
}

void CollisionScene::Render(HDC hdc)
{
	_fixedCircle->Render(hdc);
	_movableRect->Render(hdc);
}
