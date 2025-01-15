#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void PSSet(int slot);

private:
	ScratchImage image;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
};

