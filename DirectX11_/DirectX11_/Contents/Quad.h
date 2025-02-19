#pragma once
class Quad
{
public:
	// TextureMapping�� �⺻
	Quad(wstring path);
	~Quad();
	
	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }
	Vector ImageSize() { return _srv->GetSize(); }

	void SetFlipX(int value) { _flipBuffer->SetData(value); _flipBuffer->Update(); }

private:
	// mesh
	void CreateVertices();
	vector<Vertex_Texture>	 _vertices;
	vector<UINT>			 _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	// material
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;

	// Transform
	shared_ptr<Transform> _transform; // <= ���忡 �����ϱ� ���� �ʿ�����
	shared_ptr<FlipBuffer> _flipBuffer;
};

