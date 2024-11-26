#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

private:
	// �Է����� �¿�� �����̰� ����� �Լ�
	void InputMove();
	// �Է����� �ѽ��� ������ +,-�� �ǰ� ����� �Լ�
	void InputBarrelRotation();

private:
	shared_ptr<CircleCollider> _body;
	shared_ptr<Line> _barrel;
};

