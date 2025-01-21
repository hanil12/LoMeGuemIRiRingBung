cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexOuput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

VertexOuput VS(VertexInput input)
{
    // 각 정점에 대해서 필요한 계산
    VertexOuput output;
    output.pos = input.pos;
    output.pos = mul(output.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}