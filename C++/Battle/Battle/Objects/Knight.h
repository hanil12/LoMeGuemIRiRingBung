#pragma once

class Knight : public Player
{
public:
	Knight(string name, int hp, int atk);
	~Knight() { cout << "Knight deleted" << endl; }

	// 함수 오버라이딩 : 부모의 함수를 자식에 재정의
	// 재정의... 함수시그니쳐가 동일
	virtual void Attack(shared_ptr<Creature> monster);

private:
};

