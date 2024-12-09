#pragma once
class Line
{
public:
	struct HitResult
	{
		bool isCollision = false;
		Vector hitPoint;
	};

	Line(Vector start, Vector end);
	~Line();

	void Update();
	void Render(HDC hdc);

	void SetRed() { _curColor = 0; }
	void SetGreen() { _curColor = 1; }

	HitResult IsCollision(shared_ptr<Line> other);
	bool IsBetween(Vector center, Vector left, Vector right);

public:
	Vector _start;
	Vector _end;

	HPEN _colors[2];
	int _curColor = 1;
};

