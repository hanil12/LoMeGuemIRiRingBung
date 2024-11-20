#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
    _pens.reserve(3);
    {
        _pens.push_back(CreatePen(3,3,RGB(255,0,0))); // »¡
        _pens.push_back(CreatePen(3,3,RGB(0,255,0))); // ÃÊ
        _pens.push_back(CreatePen(3,3,RGB(0,0,255))); // ÆÄ
    }

    _brushes.reserve(3);
    {
        _brushes.push_back(CreateSolidBrush(RGB(255,0,0)));
        _brushes.push_back(CreateSolidBrush(RGB(0,255,0)));
        _brushes.push_back(CreateSolidBrush(RGB(0,0,255)));
    }

    myCircle->SetRed();
    rect->SetGreen();
}

PaintScene::~PaintScene()
{
    for(auto pen : _pens)
        DeleteObject(pen);

    for(auto brush : _brushes)
        DeleteObject(brush);

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

    SelectObject(hdc, _pens[2]);
    line->Render(hdc);
}
