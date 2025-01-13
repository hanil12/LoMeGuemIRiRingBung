
// SV : 시스템 벨류
// semantic : 의미
float4 VS(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

// 각 픽셀마다 계산되는 공식
float4 PS() : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}