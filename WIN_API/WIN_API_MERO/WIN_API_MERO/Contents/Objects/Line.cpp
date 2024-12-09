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

Line::HitResult Line::IsCollision(shared_ptr<Line> other)
{
	Vector line1_s = _start;
	Vector line1_e = _end;
	
	Vector line2_s = other->_start;
	Vector line2_e = other->_end;

	Vector line1_sTos = line2_s - line1_s;
	Vector line1_sToe = line2_e - line1_s;

	Vector line2_sTos = line1_s - line2_s;
	Vector line2_sToe = line1_e - line2_s;

	bool isBetween1 = IsBetween((line1_e - line1_s), line1_sTos, line1_sToe);
	bool isBetween2 = IsBetween((line2_e - line2_s), line2_sTos, line2_sToe);

	float left = fabs((line2_e - line2_s).Cross(line1_s - line2_s));
	float right = fabs((line2_e - line2_s).Cross(line1_e - line2_s));

	float ratio = left / (left + right);

	Line::HitResult result;
	result.isCollision = isBetween1 && isBetween2;
	result.hitPoint = LinearInterpolation(line1_s, line1_e, ratio);

	return result;
}

bool Line::IsBetween(Vector center, Vector left, Vector right)
{
	float Cross1_s = center.Cross(left); // +
	float Cross1_e = center.Cross(right); // -

	float result = Cross1_e * Cross1_s;

	return result < 0;
}
