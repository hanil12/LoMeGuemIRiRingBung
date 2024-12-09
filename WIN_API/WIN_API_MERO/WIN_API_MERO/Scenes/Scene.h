#pragma once
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void PostInitilize() abstract;

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
};

