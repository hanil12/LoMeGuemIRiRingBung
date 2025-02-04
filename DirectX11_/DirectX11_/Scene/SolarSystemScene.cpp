#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_earthParent = make_shared<Transform>();
	_moonParent = make_shared<Transform>();

	_sun = make_shared<Quad>(L"Resource/sun.png");
	_earth = make_shared<Quad>(L"Resource/earth.png");
	_moon = make_shared<Quad>(L"Resource/moon.png");

	_sun->GetTransform()->SetScale({0.5f, 0.5f});
	_sun->GetTransform()->SetLocalLocation(CENTER);

	_earth->GetTransform()->SetScale({0.1f, 0.1f});
	_earth->GetTransform()->SetLocalLocation(Vector(300,0));

	_moon->GetTransform()->SetScale({0.05f,0.05f});
	_moon->GetTransform()->SetLocalLocation(Vector(100,0));

	// Matrix의 종속
	// => 좌표계 변환
	_earth->GetTransform()->SetParent(_earthParent);
	_moon->GetTransform()->SetParent(_moonParent);
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sun->Update();
	_earth->Update();
	_moon->Update();
	_earthParent->Update();
	_moonParent->Update();

	_sun->GetTransform()->SetLocalLocation(mousePos);

	_earthParent->SetLocalLocation(_sun->GetTransform()->GetWorldLocation());
	_moonParent->SetLocalLocation(_earth->GetTransform()->GetWorldLocation());

	_sun->GetTransform()->AddAngle(0.0001f);
	_earth->GetTransform()->AddAngle(0.0005f);
	_moon->GetTransform()->AddAngle(0.0005f);

	_earthParent->AddAngle(0.0002f);
	_moonParent->AddAngle(0.0001f);
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
	_moon->Render();
}
