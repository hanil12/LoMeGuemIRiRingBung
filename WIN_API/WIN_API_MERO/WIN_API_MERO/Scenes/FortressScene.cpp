#include "framework.h"
#include "FortressScene.h"

#include "Contents/GameObject/Cannon.h"

FortressScene::FortressScene()
{
	_cannon1 = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();
}

FortressScene::~FortressScene()
{
}

void FortressScene::PostInitilize()
{
	_cannon1->PostInitilize();
	_cannon2->PostInitilize();
}

void FortressScene::Update()
{
	_cannon1->Update();
	_cannon2->Update();
}

void FortressScene::Render(HDC hdc)
{
	_cannon1->Render(hdc);
	_cannon2->Render(hdc);
}
