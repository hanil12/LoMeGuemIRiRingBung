#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	void Update() override;
	void Render() override;

	void Input();

private:
	shared_ptr<CircleCollider> _circleCollider1;
	shared_ptr<CircleCollider> _circleCollider2;
	shared_ptr<CircleCollider> _circleCollider3;
	shared_ptr<RectCollider> _rectCollider;
};

