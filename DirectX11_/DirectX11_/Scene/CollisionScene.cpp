#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circleCollider = make_shared<CircleCollider>(CENTER, 100);
	_rectCollider = make_shared<RectCollider>(CENTER - Vector(0,100), Vector(100,100));
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
	if (GetKeyState('W') & 0x8000)
	{
		_circleCollider->GetTransform()->AddScale(Vector(0.001f, 0.001f));
		//_rectCollider->GetTransform()->AddScale(Vector(0.001f, 0.001f));
	}

	if (GetKeyState('S') & 0x8000)
	{
		_circleCollider->GetTransform()->AddScale(Vector(-0.001f, -0.001f));
		//_rectCollider->GetTransform()->AddScale(Vector(-0.001f, -0.001f));
	}
}
