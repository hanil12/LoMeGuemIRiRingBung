#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

private:
	void CreateBlob(wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	Microsoft::WRL::ComPtr<ID3DBlob>				 vertexBlob;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		 inputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		 vertexShader;
};

