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
	// �Է����� �¿�� �����̰� ����� �Լ�
	void InputMove();
	// �Է����� �ѽ��� ������ +,-�� �ǰ� ����� �Լ�
	void InputBarrelRotation();

private:
	shared_ptr<CircleCollider> _body;
	shared_ptr<class Barrel> _barrel;

	int _poolCount = 30;
	vector<shared_ptr<class Ball>> _ballPool;

	float _fireDelay = 1.0f; // 1�ʸ� ��Ȯ�� �� �� ������? X
	float _fireTime = 0.0f;

	// Delegate
	function<void(shared_ptr<Cannon>)> _fireEvent; // �����Լ� OK, ����Լ� OK, �Լ���ü OK => ��� Callable ��ü�� ���� �� �ִ� �Լ� ������
	//using FUNC = void(*)(void); // �����Լ� �Ű����� void, ��ȯ�ڷ��� void�� ������ �� �ִ� �Լ� ������
	//template<typename T>
	//using FUNC_SCENE = void(T::*)(void); // Scene�� ����Լ� �Ű�����(void), ��ȯ�ڷ��� void �Լ��� ������ �� �ִ� �Լ�������
};

