#include "framework.h"
#include "DungreedScene.h"

#include "Contents/ArrowScene/Player.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>();
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	_player->PreUpdate();
}

void DungreedScene::Update()
{
	_player->Update();
}

void DungreedScene::Render()
{
	_player->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();
}
