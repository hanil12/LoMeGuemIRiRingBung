
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Flip : register(b0)
{
    int leftRight;
    int padding[3];
}

cbuffer Slider : register(b1)
{
    float value;
    int padding2[3];
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

// 각 픽셀마다 계산되는 공식
float4 PS(PixelInput input) : SV_TARGET
{
    if (leftRight != 0)
        input.uv.x *= -1;
    
    if (input.uv.x > value)
    {
        return float4(0, 0, 0, 0);
    }
    
    return map.Sample(samp, input.uv);

}