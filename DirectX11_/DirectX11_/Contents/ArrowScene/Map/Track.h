#pragma once

class Player;
class Track
{
public:
	Track();
	~Track();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void Block(shared_ptr<Player> player);

private:
	shared_ptr<Quad> _image;
	shared_ptr<RectCollider> _rect;
};

