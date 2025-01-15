#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        IN _srv.ReleaseAndGetAddressOf());
}

SRV::~SRV()
{
    image.Release();
}

void SRV::PSSet(int slot)
{
    DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}
