#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	~DungreedScene();

	virtual void PreUpdate() override;
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class Player> _player;
	shared_ptr<Quad> _bg;
	shared_ptr<class Track> _track;
};

