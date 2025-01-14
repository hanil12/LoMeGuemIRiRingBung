
Texture2D map : register(t0);
SamplerState samp : register(s0);

// SV : 시스템 벨류
// semantic : 의미

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

PixelInput VS(VertexInput input)
{
    // 계산
    PixelInput output;
    output.pos = input.pos;
    output.uv = input.uv;
    
    return output;
}

// 각 픽셀마다 계산되는 공식
float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, input.uv);

}