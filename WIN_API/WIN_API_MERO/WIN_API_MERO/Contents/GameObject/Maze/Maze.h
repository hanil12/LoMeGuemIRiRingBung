#pragma once

#include "Contents/GameObject/Maze/Block.h"

#define MAX_X 31
#define MAX_Y 31

class Maze
{
public:
	struct Edge
	{
		Vector u;
		Vector v;

		float cost;
	};

	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	void CreateMaze_Kruskal();

	Vector GetStartPos() { return {1,1}; }
	Vector GetEndPos() { return {MAX_X - 2, MAX_Y - 2 }; }

	Block::BlockType GetBlockType(int y, int x) { return _blocks[y][x]->GetType(); }
	void SetBlockType(int y, int x, Block::BlockType type) { _blocks[y][x]->SetType(type); }

private:
	vector<vector<shared_ptr<Block>>> _blocks; // 25 x 25
};

