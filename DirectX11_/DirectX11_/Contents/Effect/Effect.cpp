#include "framework.h"
#include "Effect.h"

Effect::Effect(wstring file, Vector maxFrame, float speed, Action::Type type)
{
	_sprite = make_shared<Sprite>(file, maxFrame);

	CreateClips(file, maxFrame, speed, type);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if (_isActive == false) return;

	_action->Update();
	_sprite->Update();
}

void Effect::Render()
{
	if(_isActive == false) return;

	_sprite->SetCurFrame(_action->GetCurClip());
	_sprite->Render();
}

void Effect::PostRender()
{
}

void Effect::SetScale(Vector scale)
{
	_sprite->GetTransform()->SetScale(scale);
}

void Effect::Play(Vector pos)
{
	_isActive = true;
	_sprite->GetTransform()->SetLocalLocation(pos);
	_action->Play();
}

void Effect::End()
{
	_isActive = false;
	_action->Reset();
}

void Effect::CreateClips(wstring file, Vector maxFrame, float speed, Action::Type type)
{
	Vector clipsSize = _sprite->ImageSize();
	clipsSize.x = clipsSize.x / maxFrame.x;
	clipsSize.y = clipsSize.y / maxFrame.y;

	vector<Action::Clip> clips;
	
	for(int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			Action::Clip clip = Action::Clip(x * clipsSize.x, y * clipsSize.y,clipsSize.x,clipsSize.y, ADD_SRV(file));
			clips.push_back(clip);
		}
	}

	string name = string(file.begin(), file.end());
	_action = make_shared<Action>(clips, name, type, speed);

	_action->SetEndEvent(std::bind(&Effect::End, this));
}
