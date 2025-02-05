#include "framework.h"
#include "Arrow.h"

Arrow::Arrow()
{
	isActive = false;
	_arrow = make_shared<Quad>(L"Resource/Bullet.png");
	_arrow->GetTransform()->SetLocalLocation(Vector(-1000,-1000));
	_arrow->GetTransform()->SetScale(Vector(0.16f, 0.16f));
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if(!isActive) return;

	_arrow->Update();

	_arrow->GetTransform()->AddLocalLocation(_dir * 0.1f);
}

void Arrow::Render()
{
	if(!isActive) return;

	_arrow->Render();
}
