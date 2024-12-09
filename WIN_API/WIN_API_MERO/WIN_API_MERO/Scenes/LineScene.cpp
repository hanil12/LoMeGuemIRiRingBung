#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<Line>(Vector(100,100), Vector(0,0));
	_line2 = make_shared<Line>(Vector(0,500), Vector(1280,500));
	_line3 = make_shared<Line>(Vector(100,400), Vector(800,100));

	_circle = make_shared<CircleCollider>(Vector(0,0), 30);
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_line1->_end = mousePos;

	Line::HitResult result = _line1->IsCollision(_line3);
	if (result.isCollision)
	{
		_line1->SetRed();
		_line2->SetRed();

		_circle->Center() = result.hitPoint;
	}
	else
	{
		_line1->SetGreen();
		_line2->SetGreen();

		_circle->Center() = Vector(-10000,0);
	}

	_line1->Update();
	_line3->Update();
	_circle->Update();
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line3->Render(hdc);
	_circle->Render(hdc);
}
