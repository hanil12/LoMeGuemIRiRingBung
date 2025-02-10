#include "framework.h"
#include "BowScene.h"

#include "Contents/ArrowScene/Arrow.h"

BowScene::BowScene()
{
	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bow->GetTransform()->SetLocalLocation(Vector(100,100));
	_bow->GetTransform()->SetScale(Vector(0.16f,0.16f));

	for (int i = 0; i < 100; i++)
	{
		_arrows.push_back(make_shared<Arrow>());
	}

	_rect = make_shared<RectCollider>(CENTER, Vector(50,50));
}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	_rect->Update();

	_bow->Update();

	Vector dir = mousePos - _bow->GetTransform()->GetLocalLocation();
	dir.Normalize();
	_bow->GetTransform()->SetAngle(dir.Angle());

	for (auto arrow : _arrows)
	{
		arrow->Update();
	}

	Fire();
}

void BowScene::Render()
{
	_bow->Render();
	for (auto arrow : _arrows)
	{
		arrow->Render();
	}

	_rect->Render();
}

void BowScene::Fire()
{
	_delay += 0.001f;

	if ((GetKeyState(VK_LBUTTON) & 0x8000) && (_delay > 1.0f))
	{
		auto iter = std::find_if(_arrows.begin(), _arrows.end(), [](const shared_ptr<Arrow>& arrow)->bool 
		{
			if(arrow->isActive == false)
				return true;
			return false;
		});

		if (iter != _arrows.end())
		{
			(*iter)->isActive = true;
			(*iter)->SetDir(mousePos - _bow->GetTransform()->GetLocalLocation());
			(*iter)->SetLocation(_bow->GetTransform()->GetLocalLocation()); // TODO : 총구위치 찾기
			_delay = 0.0f;
		}
	}
}
