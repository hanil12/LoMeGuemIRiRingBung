#include "framework.h"
#include "Arrow.h"

Arrow::Arrow()
{
	isActive = false;
	_arrow = make_shared<Quad>(L"Resource/Bullet.png");
	_arrow->GetTransform()->SetLocalLocation(Vector(-1000,-1000));
	_arrow->GetTransform()->SetScale(Vector(0.16f, 0.16f));

	_collider = make_shared<CircleCollider>(Vector(100,0), 50);
	_collider->GetTransform()->SetParent(_arrow->GetTransform());
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if(!isActive) return;

	_collider->Update();

	_arrow->Update();

	_arrow->GetTransform()->AddLocalLocation(_dir * _speed * DELTA_TIME);
}

void Arrow::Render()
{
	if(!isActive) return;

	_arrow->Render();
}

void Arrow::PostRender()
{
	if(!isActive) return;

	_collider->Render();
}
