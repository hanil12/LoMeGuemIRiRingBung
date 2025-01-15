#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_vertexBuffer = make_shared<VertexBuffer>();

	_vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");
	_samplerState = make_shared<SamplerState>();
	_srv = make_shared<SRV>(L"Resource/SCS.png");
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
    // IA : Input Assembler : 입력 병합
    _vs->SetInputLayout();
    _vertexBuffer->SetVertexBuffer(0);

    _srv->PSSet(0);
    _samplerState->PSSet(0);

    _vs->SetShader();
    _ps->SetShader();

    // 정점의 개수
    DC->Draw(6,0);
}
