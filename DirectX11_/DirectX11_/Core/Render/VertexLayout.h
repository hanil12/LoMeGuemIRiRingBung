#pragma once

struct Vertex
{
    Vertex() {}
    Vertex(XMFLOAT3 pos) : pos(pos) {}

    XMFLOAT3 pos = {0.0f,0.0f,0.0f};
};

struct Vertex_Texture
{
    Vertex_Texture() {}
    Vertex_Texture(XMFLOAT3 pos) : pos(pos) {}

    XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
    XMFLOAT2 uv = {0.0f, 0.0f}; // 텍스쳐좌표
};