#pragma once
class CircleCollider
{
public:
	CircleCollider(Vector center, float radius);
	~CircleCollider();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetRed() { _colorBuffer->SetData(XMFLOAT4(1, 0, 0, 1)); }
	void SetGreen() { _colorBuffer->SetData(XMFLOAT4(0, 1, 0, 1)); }

	Vector Center() { return _transform->GetWorldLocation(); }
	float Radius() { return _radius * _transform->GetWorldScale().x; }

	// 1. 점충돌 구현
	// 2. CircleCollider
	bool IsCollision(const Vector& pos);
	bool IsCollision(shared_ptr<CircleCollider> other);

private:
	void CreateVertices();

	vector<Vertex>	 _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	float _radius;
};

