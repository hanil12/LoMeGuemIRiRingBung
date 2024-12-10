#pragma once

class Block;

#define MAX_X 25
#define MAX_Y 25

class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

private:
	vector<vector<shared_ptr<Block>>> _blocks; // 25 x 25
};

