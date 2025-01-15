#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

private:
	void CreateBlob(wstring file);
	void CreatePixelShader();

	Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

