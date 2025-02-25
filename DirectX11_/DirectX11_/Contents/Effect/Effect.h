#pragma once
class Effect
{
public:
	Effect(wstring file, Vector maxFrame, float speed = 0.1f, Action::Type type = Action::END);
	~Effect();

	void Update();
	void Render();
	void PostRender();

	void SetScale(Vector scale);
	void Play(Vector pos);
	void End();

	bool _isActive;
private:
	void CreateClips(wstring file, Vector maxFrame, float speed = 0.1f, Action::Type type = Action::END);

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

