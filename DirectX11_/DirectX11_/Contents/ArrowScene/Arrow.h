#pragma once
class Arrow
{
public:
	Arrow();
	~Arrow();

	void Update();
	void Render();
	void PostRender();

	void SetLocation(Vector pos) { _arrow->GetTransform()->SetLocalLocation(pos); }
	void SetDir(Vector dir) { _dir = dir.NormalVector(); _arrow->GetTransform()->SetAngle(_dir.Angle()); }

	bool isActive;
private:
	shared_ptr<Quad> _arrow;
	shared_ptr<CircleCollider> _collider;
	Vector _dir;
	float _speed = 300.0f;
};

