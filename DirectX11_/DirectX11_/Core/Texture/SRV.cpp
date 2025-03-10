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

Vector SRV::GetSize()
{
    if(image.GetImageCount() == 0)
        return Vector(0,0);

    return Vector(image.GetMetadata().width, image.GetMetadata().height);
}
