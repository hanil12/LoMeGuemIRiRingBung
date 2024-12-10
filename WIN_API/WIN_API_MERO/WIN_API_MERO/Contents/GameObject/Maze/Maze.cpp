#include "framework.h"
#include "Maze.h"
#include "Block.h"

Maze::Maze()
{
	Vector offset = Vector(300,100);

	_blocks.resize(25);
	for (int y = 0; y < MAX_Y; y++)
	{
		_blocks[y].reserve(25);
		for (int x = 0; x < MAX_X; x++)
		{
			shared_ptr<Block> block = make_shared<Block>();
			Vector pos;
			pos.y = y * 15;
			pos.x = x * 15;
			block->SetPos(pos + offset);
			block->SetType(Block::ABLE);

			_blocks[y].push_back(block);
		}
	}
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blocks : _blocks)
	{
		for (auto block : blocks)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blocks : _blocks)
	{
		for (auto block : blocks)
		{
			block->Render(hdc);
		}
	}
}
