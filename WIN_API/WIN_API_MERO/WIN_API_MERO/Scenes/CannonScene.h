#pragma once
class CannonScene : public Scene
{
public:
	CannonScene();
	~CannonScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<class Cannon> _cannon;
};

