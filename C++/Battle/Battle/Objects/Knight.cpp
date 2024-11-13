#include "framework.h"
#include "Knight.h"

Knight::Knight(string name, int hp, int atk)
: Player(name, hp, atk)
{
}

void Knight::Attack(shared_ptr<Creature> monster)
{
	int atk = _atk + rand() % 5;

	float ratio = (_hp / (float)_maxHp);

	if (ratio < 0.5f)
	{
		monster->TakeDamage(atk * 2, shared_from_this());
		cout << _name << " is Attacking " << monster->GetName() << endl;
		return;
	}

	monster->TakeDamage(atk, shared_from_this());
	cout << _name << " is Attacking " << monster->GetName() << endl;
}
