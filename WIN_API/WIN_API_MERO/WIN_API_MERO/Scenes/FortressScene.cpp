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

	_cannon1->Update();
	_cannon2->Update();
}

void FortressScene::Update()
{
	_cannon1->Update();
	_cannon2->Update();

	if (_isTurn)
	{
		_cannon1->Move();

		if(_cannon1->IsFireReady())
			_cannon1->Fire(_isTurn);
	}
	else if(!_isTurn)
	{
		_cannon2->Move();

		if(_cannon2->IsFireReady())
			_cannon2->Fire(_isTurn);
	}
}

void FortressScene::Render(HDC hdc)
{
	_cannon1->Render(hdc);
	_cannon2->Render(hdc);
}
