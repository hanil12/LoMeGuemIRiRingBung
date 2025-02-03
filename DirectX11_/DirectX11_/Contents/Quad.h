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

private:
	void CreateVertices();
	vector<Vertex_Texture> vertices;

	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;

	// Transform
	shared_ptr<Transform> _transform; // <= ���忡 �����ϱ� ���� �ʿ�����
};

