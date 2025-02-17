#pragma once
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void PreUpdate() {}
	virtual void Update() abstract;

	virtual void Render() abstract;
	virtual void PostRender() {}
};

