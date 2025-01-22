#pragma once
class Quad
{
public:
	// TextureMapping을 기본
	Quad(wstring path);
	~Quad();
	
	void Update();
	void Render();

private:
	void CreateVertices();
	vector<Vertex_Texture> vertices;

	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<SRV> _srv;

	// Transform
	shared_ptr<Transform> _transform; // <= 월드에 존재하기 위한 필요조건
};

