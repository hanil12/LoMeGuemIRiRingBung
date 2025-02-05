#pragma once
class Arrow
{
public:
	Arrow();
	~Arrow();

	void Update();
	void Render();

	void SetLocation(Vector pos) { _arrow->GetTransform()->SetLocalLocation(pos); }
	void SetDir(Vector dir) { _dir = dir.NormalVector(); _arrow->GetTransform()->SetAngle(_dir.Angle()); }

	bool isActive;
private:
	shared_ptr<Quad> _arrow;
	Vector _dir;
};

