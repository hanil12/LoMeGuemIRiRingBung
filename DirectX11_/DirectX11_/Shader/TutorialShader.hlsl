
// SV : �ý��� ����
// semantic : �ǹ�
float4 VS(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

// �� �ȼ����� ���Ǵ� ����
float4 PS() : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}