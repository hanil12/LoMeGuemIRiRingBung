#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void SetVertexBuffer(int slot);

private:
	void CreateVertices();
	void CreateVertexBuffer();

	vector<Vertex_Texture> vertices;

	UINT stride;
	UINT offset;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

