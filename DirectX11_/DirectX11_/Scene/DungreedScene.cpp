#include "framework.h"
#include "DungreedScene.h"

#include "Contents/ArrowScene/Player.h"
#include "Contents/ArrowScene/Map/Track.h"
#include "Contents/UI/HpBar.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>();
	_bg = make_shared<Quad>(L"Resource/bg.png");
	_track = make_shared<Track>();
	_UIhpBar = make_shared<HpBar>(CENTER + Vector(-360,300), Vector(300,50));

	_effect = make_shared<Effect>(L"Resource/Effects/hit2_4x4.png", Vector(4,4),0.1f, Action::LOOP);
	_effect->Play(CENTER);

	_bg->GetTransform()->SetLocalLocation(CENTER);

	_bg->Update();
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	_track->PreUpdate();
	_player->PreUpdate();
}

void DungreedScene::Update()
{
	_player->Update();
	_track->Update();
	_effect->Update();
	_UIhpBar->Update();

	_track->Block(_player);
}

void DungreedScene::Render()
{
	_bg->Render();
	_track->Render();
	_effect->Render();

	_player->Render();

	_UIhpBar->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();
	_track->PostRender();
}
