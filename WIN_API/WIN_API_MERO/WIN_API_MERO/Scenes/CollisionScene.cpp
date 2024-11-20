#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_fixedCircle = make_shared<CircleCollider>(Vector(400,400), 70);
	_movableCircle = make_shared<CircleCollider>(Vector(0,0), 100);
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_fixedCircle->Update();
	_movableCircle->Update();

	//if (_fixedCircle->IsCollision(mousePos))
	//	_fixedCircle->SetRed();
	//else
	//	_fixedCircle->SetGreen();

	_movableCircle->Center() = mousePos;
}

void CollisionScene::Render(HDC hdc)
{
	_fixedCircle->Render(hdc);
	_movableCircle->Render(hdc);
}
