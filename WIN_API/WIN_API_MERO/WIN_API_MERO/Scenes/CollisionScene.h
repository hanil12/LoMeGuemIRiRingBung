#pragma once
class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Collider> _fixedCircle;
	shared_ptr<Collider> _movableCircle;
};

