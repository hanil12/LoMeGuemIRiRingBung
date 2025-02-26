#pragma once

class Quad
{
public:
	// TextureMapping을 기본
	Quad(wstring path);
	Quad(wstring path, Vector size);
	virtual ~Quad();
	
	virtual void Update();
	virtual void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }
	Vector ImageSize();

	void SetFlipX(int value) { _flipBuffer->SetData(value); _flipBuffer->Update(); }

	void SetVS(shared_ptr<VertexShader> other) { _vs = other; }
	void SetPS(shared_ptr<PixelShader> other) { _ps = other; }

protected:
	// mesh
	virtual void CreateVertices();
	vector<Vertex_Texture>	 _vertices;
	vector<UINT>			 _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	// material
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	wstring _srvPath;

	// Transform
	shared_ptr<Transform> _transform; // <= 월드에 존재하기 위한 필요조건
	shared_ptr<FlipBuffer> _flipBuffer;

	Vector _halfSize = Vector(0,0);
};

