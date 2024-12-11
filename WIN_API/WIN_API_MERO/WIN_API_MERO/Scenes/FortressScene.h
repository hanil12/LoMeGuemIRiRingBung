#pragma once
class Cannon;

class FortressScene : public Scene
{
public:
	FortressScene();
	~FortressScene();

	virtual void PostInitilize() override;
	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<Cannon> _cannon1;
	shared_ptr<Cannon> _cannon2;

	bool _isTurn;
};

