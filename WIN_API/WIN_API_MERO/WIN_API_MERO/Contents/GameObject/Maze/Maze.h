#pragma once

#include "Contents/GameObject/Maze/Block.h"

#define MAX_X 25
#define MAX_Y 25

class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

	Vector GetStartPos() { return {1,1}; }
	Vector GetEndPos() { return {MAX_X - 2, MAX_Y - 2 }; }

	Block::BlockType GetBlockType(int y, int x) { return _blocks[y][x]->GetType(); }
	void SetBlockType(int y, int x, Block::BlockType type) { _blocks[y][x]->SetType(type); }

private:
	vector<vector<shared_ptr<Block>>> _blocks; // 25 x 25
};

