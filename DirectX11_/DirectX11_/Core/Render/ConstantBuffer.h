#pragma once
// vertex 버퍼
// 행렬 넘겨주는데 vertex버퍼 주면 되는 거 아니냐?
// 
// 상수버퍼 : ?

class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	void Update();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;

	void* _data; // 행렬
	UINT _dataSize;
};

