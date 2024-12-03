#pragma once
class Barrel
{
public:
	Barrel();
	~Barrel();

	void Update();
	void Render(HDC hdc);

	void SetCannon(shared_ptr<class Cannon> cannon) { _cannon = cannon; }

	void SetDirection(Vector dir) { _direction = dir; }
	Vector GetDirection() { return _direction; }

	Vector GetMuzzle() { return _line->_end; }

private:
	shared_ptr<Line> _line;

	float _length = 150.0f;
	Vector _direction = Vector(1,0);

	// 외부에서 생성한 것을 참조하고 있을 때는 weak_ptr이 권장된다.
	weak_ptr<class Cannon> _cannon;
};

