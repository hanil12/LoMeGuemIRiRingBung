#pragma once
class Player
{
public:
	Player();
	~Player();

	void PreUpdate();
	void Update();

	void Render();
	void PostRender();

	void Input();

private:
	float _speed = 150.0f;

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _body; // Root Component
};

