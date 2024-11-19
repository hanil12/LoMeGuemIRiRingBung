#include "framework.h"
#include "Line.h"

Line::Line(Vector start, Vector end)
: _start(start)
, _end(end)
{
}

Line::~Line()
{
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, _start.x, _start.y, nullptr);
	LineTo(hdc, _end.x, _end.y);
}
