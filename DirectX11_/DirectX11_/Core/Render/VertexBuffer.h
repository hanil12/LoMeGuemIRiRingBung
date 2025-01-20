#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void * data, UINT count, UINT stride, UINT offset = 0);
	~VertexBuffer();

	void SetVertexBuffer(UINT slot);

private:
	void CreateVertexBuffer();

	UINT	_stride;
	UINT	_offset;
	UINT	_count;
	void*	_data;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
};

