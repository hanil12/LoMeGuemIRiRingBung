#pragma once
class Quad
{
public:
	// TextureMapping¿ª ±‚∫ª
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

	XMFLOAT2		 _scale; // S
	float			 _angle; // R
	XMFLOAT2		 _pos;   // Translate
	shared_ptr<MatrixBuffer> _world;
};

