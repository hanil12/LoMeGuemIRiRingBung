#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Quad>(L"Resource/sun.png");
	_earth = make_shared<Quad>(L"Resource/earth.png");
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sun->Update();
	_earth->Update();
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
}
