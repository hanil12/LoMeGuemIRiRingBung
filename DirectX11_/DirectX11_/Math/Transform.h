#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetVSSlot(int slot);

	void SetLocation(Vector pos) { _pos = pos; }
	Vector GetLocation() { return _pos; }
	void AddLocation(Vector value) { _pos += value; }

	void SetScale(Vector scale) { _scale = scale; }
	Vector GetScale() { return _scale; }
	void AddScale(Vector value) { _scale += value; }

	void SetAngle(float angle) { _angle = angle; }
	float GetAngle() { return _angle; }
	void AddAngle(float value) { _angle += value; }

private:
	Vector		 _scale; // S
	float		 _angle; // R
	Vector		 _pos;   // Translate
	shared_ptr<class MatrixBuffer> _world;
};

