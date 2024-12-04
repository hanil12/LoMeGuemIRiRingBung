#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<Line>(Vector(100,100), Vector(0,0));
	_line2 = make_shared<Line>(Vector(0,500), Vector(1280,500));
	_line3 = make_shared<Line>(Vector(100,400), Vector(150,400));
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_line1->_end = mousePos;

	_line1->Update();
	_line2->Update();
	_line3->Update();
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_line3->Render(hdc);
}
