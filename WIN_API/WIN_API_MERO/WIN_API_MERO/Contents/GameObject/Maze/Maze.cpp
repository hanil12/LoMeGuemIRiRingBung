#include "framework.h"

#include "Math/DisJointSet.h"

#include "Maze.h"
#include "Block.h"

Maze::Maze()
{
	Vector offset = Vector(400,100);

	_blocks.resize(MAX_Y);
	for (int y = 0; y < MAX_Y; y++)
	{
		_blocks[y].reserve(MAX_X);
		for (int x = 0; x < MAX_X; x++)
		{
			shared_ptr<Block> block = make_shared<Block>();
			Vector pos;
			pos.y = y * 21;
			pos.x = x * 21;
			block->SetPos(pos + offset);
			block->SetType(Block::ABLE);

			_blocks[y].push_back(block);
		}
	}

	CreateMaze_Kruskal();
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

void Maze::CreateMaze()
{
	// ����� ���� ����
	// �� �� �ִ� ��� �����
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetType(Block::BlockType::DISABLE);
			}
			else
			{
				_blocks[y][x]->SetType(Block::BlockType::ABLE);
			}
		}
	}

	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			// ������
			if (x == 1 && y == 1)
			{
				_blocks[y][x]->SetType(Block::BlockType::ABLE);
			}
			
			// ����
			if (x == MAX_X - 2 && y == MAX_Y - 2)
			{
				_blocks[y][x]->SetType(Block::BlockType::ABLE);
				continue;
			}

			// ó�� ���� ������ ������ ��
			if(x % 2 == 0 || y % 2 == 0) continue;

			// ������ �� ���� �ִ� ���� �Ʒ������� �մ´�.
			if (x == MAX_X - 2)
			{
				_blocks[y + 1][x]->SetType(Block::BlockType::ABLE);
				continue;
			}

			// �� �Ʒ��� ���� �ִ� ���� ���������θ� �մ´�.
			if (y == MAX_Y - 2)
			{
				_blocks[y][x + 1]->SetType(Block::BlockType::ABLE);
				continue;
			}

			// ������ �ƴϸ� �Ʒ������θ� �մ´�
			int randValue = rand() % 2;
			if(randValue == 0)
				_blocks[y][x + 1]->SetType(Block::BlockType::ABLE); // ������ �ձ�
			else
				_blocks[y+1][x]->SetType(Block::BlockType::ABLE); // �Ʒ��� �ձ�
		}
	}
}

void Maze::CreateMaze_Kruskal()
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetType(Block::BlockType::DISABLE);
			}
			else
			{
				_blocks[y][x]->SetType(Block::BlockType::ABLE);
			}
		}
	}

	// Edge�� ����� �۾�
	vector<Edge> edges;
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			// ��尡 �ƴϸ� PASS
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// ���������ΰ��� edge������ �־��ֱ�
			if (x < MAX_X - 2)
			{
				int randCost = rand() % 100;

				Edge edge;
				edge.cost = randCost;
				edge.u = Vector(x,y);
				edge.v = Vector(x + 2, y);

				edges.push_back(edge);
			}

			// �Ʒ��� ���� �������� ���� �־��ֱ�
			if (y < MAX_Y - 2)
			{
				int randCost = rand() % 100;

				Edge edge;
				edge.cost = randCost;
				edge.u = Vector(x,y);
				edge.v = Vector(x, y + 2);

				edges.push_back(edge);
			}
		}
	}

	// Sorting
	std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)->bool 
	{
		if(a.cost < b.cost)
			return true;
		return false;
	});

	DisJointSet set((MAX_Y + 1) * MAX_X);
	for (auto& edge : edges)
	{
		int u = edge.u.y * (MAX_Y) + edge.u.x;
		int v = edge.v.y * (MAX_Y) + edge.v.x;

		if(set.FindLeader(u) == set.FindLeader(v))
			continue;

		set.Merge(u,v);

		// ������ ã��
		int x = ((int)edge.v.x + (int)edge.u.x) / 2;
		int y = ((int)edge.v.y + (int)edge.u.y) / 2;

		_blocks[y][x]->SetType(Block::BlockType::ABLE);
	}
}
