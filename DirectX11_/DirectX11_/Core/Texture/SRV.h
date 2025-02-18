#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void PSSet(int slot);
	Vector GetSize();

private:
	ScratchImage image;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
};

