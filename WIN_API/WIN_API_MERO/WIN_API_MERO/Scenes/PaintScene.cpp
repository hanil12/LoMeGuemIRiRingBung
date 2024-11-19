#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
    rect->Center() = LinearInterpolation(rect->Center(), mousePos, 0.1f);
    myCircle->Center() = mousePos;

    myCircle->Update();
    rect->Update();
    line->Update();
}

void PaintScene::Render(HDC hdc)
{
    rect->Render(hdc);
    myCircle->Render(hdc);
    line->Render(hdc);
}
