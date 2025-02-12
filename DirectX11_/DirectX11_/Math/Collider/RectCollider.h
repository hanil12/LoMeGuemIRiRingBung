#pragma once
class RectCollider
{
	struct OBB_DESC
	{
		Vector position;
		Vector direction[2];
		float length[2];
	};

public:
	RectCollider(Vector center, Vector size);
	~RectCollider();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetRed() { _colorBuffer->SetData(XMFLOAT4(1,0,0,1)); }
	void SetGreen() { _colorBuffer->SetData(XMFLOAT4(0,1,0,1)); }

	OBB_DESC GetOBB();
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

