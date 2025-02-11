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
	shared_ptr<CircleCollider> _circleCollider;
	shared_ptr<RectCollider> _rectCollider;
};

