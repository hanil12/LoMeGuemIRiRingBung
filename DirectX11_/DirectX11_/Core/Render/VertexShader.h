#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void SetInputLayout();
	void SetShader();

private:
	void CreateBlob(wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	Microsoft::WRL::ComPtr<ID3DBlob>				 _vertexBlob;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		 _inputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		 vertexShader;

	//UPROPERY(Vis)
	// - 府敲泛记
	// - 皋葛府 包府
	// UStataicMeshComponent* _temp;

	Microsoft::WRL::ComPtr<ID3D11ShaderReflection>	 _reflection;
};

