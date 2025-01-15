#pragma once

struct Vertex
{
    Vertex() {}
    Vertex(XMFLOAT3 pos) : pos(pos) {}

    XMFLOAT3 pos;
};

struct Vertex_Texture
{
    Vertex_Texture() {}
    Vertex_Texture(XMFLOAT3 pos) : pos(pos) {}

    XMFLOAT3 pos;
    XMFLOAT2 uv; // 텍스쳐좌표
};