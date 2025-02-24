
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Flip : register(b0)
{
    int leftRight;
    int padding[3];
}

cbuffer Frame : register(b1)
{
    float2 maxFrame; // 이미지의 전체 프레임
    float2 curFrame; // 이미지의 현재 프레임
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

// 각 픽셀마다 계산되는 공식
float4 PS(PixelInput input) : SV_TARGET
{
    float2 spriteUV = float2(0,0);
    spriteUV.x = (input.uv.x / maxFrame.x + curFrame.x / maxFrame.x);
    spriteUV.y = (input.uv.y / maxFrame.y + curFrame.y / maxFrame.y);
    
    if (leftRight != 0)
        spriteUV.x *= -1;
    
    return map.Sample(samp, spriteUV);

}