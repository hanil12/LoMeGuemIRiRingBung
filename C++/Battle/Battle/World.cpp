#include "framework.h"
#include "World.h"

World::World()
{
	Init();
}

World::~World()
{

}

void World::Init()
{
	_boss = make_shared<Boss>();

	for (int i = 0; i < 10; i++)
	{
		auto player = make_shared<Knight>("K" + to_string(i), 100, 5);

		_players.push_back(player);
	}
}

void World::Update()
{
	shared_ptr<Boss> curBoss = dynamic_pointer_cast<Boss>(_boss);
	if (curBoss != nullptr)
	{
		curBoss->AttackPlayers();
	}

	for (auto player : _players)
	{
		player->Attack(_boss);
	}
}

bool World::End()
{
	if(_boss->IsDead() == true)
		return true;

	bool check = true;
	for (auto p : _players)
	{
		if (p->IsDead() == false)
		{
			check = false;
			break;
		}
	}

	if(check)
		return true;

	return false;
}
