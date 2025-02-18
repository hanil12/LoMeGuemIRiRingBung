
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Flip : register(b0)
{
    int leftRight;
    int padding[3];
}


struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};


// �� �ȼ����� ���Ǵ� ����
float4 PS(PixelInput input) : SV_TARGET
{
    if (leftRight != 0)
        input.uv.x *= -1;
    
    return map.Sample(samp, input.uv);

}