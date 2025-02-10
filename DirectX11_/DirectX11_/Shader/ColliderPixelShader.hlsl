cbuffer Color : register(b0)
{
    float4 color;
}

struct PixelInput
{
    float4 pos : SV_POSITION;
};


// 각 픽셀마다 계산되는 공식
float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}