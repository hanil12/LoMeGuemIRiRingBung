#include "framework.h"
#include "Boss.h"

Boss::Boss()
: Goblin("Boss")
{
	_hp = 10000;
	_atk = 20;
}

Boss::~Boss()
{
}

void Boss::AttackPlayers()
{
	if(_aggroTable.size() == 0)
		return;

	auto iter = std::remove_if(_aggroTable.begin(), _aggroTable.end(), [](const PlayerInfo& info)-> bool 
	{
		if (info.p.expired() == false)
		{
			auto player = info.p.lock();

			if(player->IsDead() == true)
				return true;
			else return false;
		}
		else
			return true;
	});

	_aggroTable.erase(iter, _aggroTable.end());

	std::sort(_aggroTable.begin(), _aggroTable.end(), greater<PlayerInfo>());

	PrintTable();

	int range = 4;

	if(range > _aggroTable.size()) range = _aggroTable.size();

	for (int i = 0; i < range; i++)
	{
		Attack(_aggroTable[i].p.lock());
		_aggroTable[i].p.lock()->PrintInfo();
	}
}

void Boss::Attack(shared_ptr<Creature> other)
{
	Creature::Attack(other);
}

void Boss::TakeDamage(int amount, shared_ptr<Creature> attacker)
{
	Creature::TakeDamage(amount, nullptr);

	// AggroTable에 등록
	auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(), [attacker](const PlayerInfo& info)-> bool
	{
			if (info.p.lock().get() == attacker.get())
			{
				return true;
			}

			return false;
	});

	// 없었다.
	if (iter == _aggroTable.end())
	{
		PlayerInfo info = { dynamic_pointer_cast<Player>(attacker), amount};
		_aggroTable.push_back(info);
	}
	// 있었다.
	else 
	{
		iter->totalDamage += amount;
	}
}

void Boss::PrintTable()
{
	for (auto info : _aggroTable)
	{
		if (info.p.expired() == false)
		{
			auto temp = info.p.lock();
			cout << "Player : " <<temp->GetName() << " / Total Damage: " << info.totalDamage << endl;
		}
	}
}
