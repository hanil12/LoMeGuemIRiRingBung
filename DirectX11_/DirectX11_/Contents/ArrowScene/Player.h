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
	void Jump();

	shared_ptr<RectCollider> Collider() { return _body; }
	bool& IsFalling() { return _isFalling; }

private:
	float _speed = 150.0f;

	bool _isFalling = true;
	float _jumpForce = 0.0f;

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _body; // Root Component
};

