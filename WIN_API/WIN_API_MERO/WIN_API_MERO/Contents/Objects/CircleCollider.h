#pragma once
// 1. 색
// 2. 상속관계 정의
// 3. 충돌처리(AABB, OBB)
class RectCollider;


// Collider : 충돌체
class CircleCollider : public Collider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	float& Radius() { return _radius; }

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool IsCollision(const Vector& pos) const override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) const override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) const override;

private:
	float		 _radius;
};

