#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetVSSlot(int slot);

	void SetLocalLocation(Vector pos) { _pos = pos; Update(); }
	Vector GetLocalLocation() { return _pos; }
	void AddLocalLocation(Vector value) { _pos += value; }

	Vector GetWorldLocation();
	Vector GetWorldScale();

	void SetScale(Vector scale) { _scale = scale; Update(); }
	Vector GetScale() { return _scale; }
	void AddScale(Vector value) { _scale += value; }

	void SetAngle(float angle) { _angle = angle; Update(); }
	float GetAngle() { return _angle; }
	void AddAngle(float value) { _angle += value; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; Update(); }
	XMMATRIX GetMatrix() { return _srtMatrix; }

private:
	weak_ptr<Transform> _parent;

	XMMATRIX	 _srtMatrix;

	Vector		 _scale; // S
	float		 _angle; // R
	Vector		 _pos;   // Translate
	shared_ptr<class MatrixBuffer> _world;
};

