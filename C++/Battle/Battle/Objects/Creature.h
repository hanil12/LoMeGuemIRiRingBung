#pragma once

// 선언부
//     [Creature]
// [player] [monster]
class Creature : public enable_shared_from_this<Creature>
{
public:
	Creature() : _name(""),_hp(0),_atk(0), _maxHp(0) {}
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	void PrintInfo();
	virtual void Attack(shared_ptr<Creature> creature);
	virtual void TakeDamage(int amount, shared_ptr<Creature> attacker = nullptr);

	bool IsDead();

	const string& GetName() { return _name; }


protected:
	int _maxHp;
	int _hp;
	int _atk;
	string _name;
};

