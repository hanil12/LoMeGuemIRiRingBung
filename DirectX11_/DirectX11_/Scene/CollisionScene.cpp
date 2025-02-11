#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circleCollider = make_shared<CircleCollider>(CENTER, 100);
	_rectCollider = make_shared<RectCollider>(CENTER - Vector(0,100), Vector(100,100));


	// circle1,2 만들고, 한 circle2을 종속 시킨 상태에서 circle1 이동 및 회전
	// extra... circle3
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_circleCollider->Update();
	_rectCollider->Update();

	Input();

	if (_circleCollider->IsCollision(mousePos))
		_circleCollider->SetRed();
	else
		_circleCollider->SetGreen();

	if(_rectCollider->IsCollision(mousePos))
		_rectCollider->SetRed();
	else
		_rectCollider->SetGreen();
}

void CollisionScene::Render()
{
	_circleCollider->Render();
	_rectCollider->Render();
}

void CollisionScene::Input()
{
	if (KEY_PRESS('W'))
	{
		_circleCollider->GetTransform()->AddScale(Vector(0.001f, 0.001f));
		//_rectCollider->GetTransform()->AddScale(Vector(0.001f, 0.001f));
	}

	if (KEY_PRESS('S'))
	{
		_circleCollider->GetTransform()->AddScale(Vector(-0.001f, -0.001f));
		//_rectCollider->GetTransform()->AddScale(Vector(-0.001f, -0.001f));
	}
}
