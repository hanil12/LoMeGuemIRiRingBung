#pragma once

class Arrow;

class BowScene : public Scene
{
public:
	BowScene();
	~BowScene();

	void Update() override;
	void Render() override;

	void Fire();

private:
	float _delay = 0.0f;

	shared_ptr<Quad> _bow;

	vector<shared_ptr<Arrow>> _arrows;
};

