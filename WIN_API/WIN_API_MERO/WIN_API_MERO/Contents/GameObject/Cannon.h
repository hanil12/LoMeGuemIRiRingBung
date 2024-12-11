#pragma once
#include "Barrel.h"

class Cannon : public enable_shared_from_this<Cannon>
{
public:
	Cannon();
	~Cannon();

	void PostInitilize() { Ready(); }
	void Update();
	void Render(HDC hdc);

	const Vector& GetCenter() { return _body->Center(); }

	void Fire(bool& turn);
	void Move();

	bool IsFireReady() 
	{
		_fireTime += 0.01f; 
		if (_fireTime > _fireDelay)
		{
			_fireTime = 0.0f;
			return true;
		}

		return false;
	}

	void SetFireEvent(function<void(shared_ptr<Cannon>)> event) { _fireEvent = event; }

	void IsDamaged(shared_ptr<class Ball> ball);

private:
	void Ready() { _barrel->SetCannon(shared_from_this()); }
	// 입력으로 좌우로 움직이게 만드는 함수
	void InputMove();
	// 입력으로 총신의 각도가 +,-가 되게 만드는 함수
	void InputBarrelRotation();

private:
	shared_ptr<CircleCollider> _body;
	shared_ptr<class Barrel> _barrel;

	int _poolCount = 30;
	vector<shared_ptr<class Ball>> _ballPool;

	float _fireDelay = 1.0f; // 1초를 정확히 할 수 있을까? X
	float _fireTime = 0.0f;

	// Delegate
	function<void(shared_ptr<Cannon>)> _fireEvent; // 전역함수 OK, 멤버함수 OK, 함수객체 OK => 모든 Callable 객체를 담을 수 있는 함수 포인터
	//using FUNC = void(*)(void); // 전역함수 매개변수 void, 반환자료형 void를 저장할 수 있는 함수 포인터
	//template<typename T>
	//using FUNC_SCENE = void(T::*)(void); // Scene의 멤버함수 매개변수(void), 반환자료형 void 함수를 저장할 수 있는 함수포인터
};

