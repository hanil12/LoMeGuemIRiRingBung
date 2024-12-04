#include "framework.h"
#include "Line.h"

Line::Line(Vector start, Vector end)
: _start(start)
, _end(end)
{
	_colors[0] = CreatePen(3,3, RED);
	_colors[1] = CreatePen(3,3, GREEN);

	SetGreen();
}

Line::~Line()
{
	for (auto& pen : _colors)
	{
		DeleteObject(pen);
	}
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _colors[_curColor]);

	MoveToEx(hdc, _start.x, _start.y, nullptr);
	LineTo(hdc, _end.x, _end.y);
}
