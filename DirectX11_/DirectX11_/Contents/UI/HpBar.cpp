#include "framework.h"
#include "HpBar.h"

HpBar::HpBar(Vector center, Vector size)
{
	_hpBar = make_shared<Quad>(L"Resource/UI/Button.png", size);
	_bg = make_shared<Quad>(L"Resource/UI/Grey.png", size);

	SetPosition(center);

	_hpBar->SetPS(make_shared<PixelShader>(L"Shader/SliderPixelShader.hlsl"));
	_sliderBuffer = make_shared<SliderBuffer>();
	SetRatio(0.5f);
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
	_bg->Update();
	_hpBar->Update();
}

void HpBar::Render()
{
	_bg->Render();
	_sliderBuffer->SetPSBuffer(1);
	_hpBar->Render();
}

void HpBar::SetPosition(Vector pos)
{
	_bg->GetTransform()->SetLocalLocation(pos);
	_hpBar->GetTransform()->SetLocalLocation(pos);
}

void HpBar::SetSize(Vector size)
{
	_bg->GetTransform()->SetScale(size);
	_hpBar->GetTransform()->SetScale(size);
}
