#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector maxFrame)
: Quad(path)
{
	_ps = make_shared<PixelShader>(L"Shader/SpritePixelShader.hlsl");
	_frameBuffer = make_shared<FrameBuffer>();
	_frameBuffer->SetMaxFrame(maxFrame);
	SetCurFrame(Vector(0,0));
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	Quad::Update();
}

void Sprite::Render()
{
	_frameBuffer->SetPSBuffer(1);
	Quad::Render();
}

void Sprite::SetCurFrame(Vector frame)
{
	_frameBuffer->SetCurFrame(frame);
	_frameBuffer->Update();
}
