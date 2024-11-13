#include "framework.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int atk)
: _name(name), _hp(hp), _atk(atk), _maxHp(hp)
{
}

Creature::~Creature()
{
	cout << "Creature deleted" << endl;
}

void Creature::PrintInfo()
{
	cout << "Name : " << _name << endl;
	cout << "HP : " << _hp << endl;
	cout << "ATK : " << _atk << endl;
}

void Creature::Attack(shared_ptr<Creature> creature)
{
	 // shared_from_this() : 이 함수를 호출한 객체를 관리하는 shared_ptr 반환.
	creature->TakeDamage(_atk, shared_from_this());
	cout << _name << " is Attacking " << creature->GetName() << endl;
}

void Creature::TakeDamage(int amount, shared_ptr<Creature> attacker)
{
	_hp -= amount;

	if (_hp < 0)
		_hp = 0;
}

bool Creature::IsDead()
{
	return _hp <= 0;
}
