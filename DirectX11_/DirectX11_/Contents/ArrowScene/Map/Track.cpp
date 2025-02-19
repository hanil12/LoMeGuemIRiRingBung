#include "framework.h"
#include "Track.h"
#include "../Player.h"

Track::Track()
{
	_image = make_shared<Quad>(L"Resource/Track.png");
	_rect = make_shared<RectCollider>(CENTER - Vector(0,390), _image->ImageSize());

	_image->GetTransform()->SetParent(_rect->GetTransform());
	_image->GetTransform()->AddLocalLocation(Vector(0,100));
	_image->Update(); // static mesh
}

Track::~Track()
{
}

void Track::PreUpdate()
{
	_rect->Update();
}

void Track::Update()
{

}

void Track::Render()
{
	_image->Render();
}

void Track::PostRender()
{
	_rect->Render();
}

void Track::Block(shared_ptr<Player> player)
{
	if (player->Collider()->IsCollision(_rect))
	{
		player->IsFalling() = false;
	}
}
