#include "framework.h"
#include "DungreedScene.h"

#include "Contents/ArrowScene/Player.h"
#include "Contents/ArrowScene/Map/Track.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>();
	_bg = make_shared<Quad>(L"Resource/bg.png");
	_track = make_shared<Track>();

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

	_track->Block(_player);
}

void DungreedScene::Render()
{
	_bg->Render();
	_track->Render();

	_player->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();
	_track->PostRender();
}
