#pragma once
#include "Contents/GameObject/Cannon.h"

class CannonScene : public Scene
{
public:
	CannonScene();
	~CannonScene();
	
	virtual void PostInitilize() override { _cannon->PostInitilize(); }
	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<class Cannon> _cannon;
};

