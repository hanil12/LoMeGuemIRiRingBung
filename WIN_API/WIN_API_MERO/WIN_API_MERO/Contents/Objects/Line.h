#pragma once
class Line
{
public:
	Line(Vector start, Vector end);
	~Line();

	void Update();
	void Render(HDC hdc);

	void SetRed() { _curColor = 0; }
	void SetGreen() { _curColor = 1; }

public:
	Vector _start;
	Vector _end;

	HPEN _colors[2];
	int _curColor = 1;
};

