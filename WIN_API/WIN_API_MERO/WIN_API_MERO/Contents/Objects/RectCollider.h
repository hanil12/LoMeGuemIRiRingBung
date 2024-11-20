#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	int Left() { return _center.x - _halfSize.x; }
	int Right() { return _center.x + _halfSize.x; }
	int Top() { return _center.y - _halfSize.y; }
	int Bottom() { return _center.y + _halfSize.y; }

	virtual bool IsCollision(const Vector& pos) const override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) const override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) const override;

private:
	Vector		 _halfSize;
};

