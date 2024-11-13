#pragma once

struct PlayerInfo
{
	weak_ptr<Player> p;
	int totalDamage;

	bool operator>(const PlayerInfo& b) const
	{
		if(totalDamage > b.totalDamage)
			return true;
		return false;
	}
};

class Boss : public Goblin
{
public:
	Boss();
	~Boss();

	void AttackPlayers();
	virtual void Attack(shared_ptr<Creature> other) override;
	virtual void TakeDamage(int amount, shared_ptr<Creature> attacker) override;

private:
	void PrintTable();
	vector<PlayerInfo> _aggroTable;
};

