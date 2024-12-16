#include "framework.h"
#include "Block.h"

Block::Block()
{
	_rect = make_shared<RectCollider>(Vector(300,300), Vector(17,17));
	_rect->SetBlack();

	_brushes.push_back(CreateSolidBrush(RGB(255,255,255)));
	_brushes.push_back(CreateSolidBrush(GREEN));
	_brushes.push_back(CreateSolidBrush(RED));
	_brushes.push_back(CreateSolidBrush(SAND_DOLLAR));
}

Block::~Block()
{
	for (int i = 0; i < _brushes.size(); i++)
	{
		DeleteObject(_brushes[i]);
	}
}

void Block::Update()
{
	_rect->Update();
}

void Block::Render(HDC hdc)
{
	SelectObject(hdc,_brushes[static_cast<unsigned int>(_curType)]);
	_rect->Render(hdc);
}
