#pragma once
class RectCollider
{
public:
	RectCollider(Vector center, Vector size);
	~RectCollider();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetRed() { _colorBuffer->SetData(XMFLOAT4(1,0,0,1)); }
	void SetGreen() { _colorBuffer->SetData(XMFLOAT4(0,1,0,1)); }

	float Left() {  return Center().x - (_halfSize.x * _transform->GetScale().x); }
	float Right() { return Center().x + (_halfSize.x * _transform->GetScale().x); }
	float Top() { return Center().y + _halfSize.y * _transform->GetScale().y; }
	float Bottom() { return Center().y - _halfSize.y * _transform->GetScale().y; }

	Vector Center() { return _transform->GetWorldLocation(); }

	// 1. 점충돌 구현
	// 2. CircleCollider
	bool IsCollision(const Vector& pos);

private:
	void CreateVertices();

	vector<Vertex>	 _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

	Vector _halfSize;
};

