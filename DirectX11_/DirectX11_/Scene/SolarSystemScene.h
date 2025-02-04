#pragma once
class SolarSystemScene : public Scene
{
public:
	SolarSystemScene();
	~SolarSystemScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _sun;
	shared_ptr<Quad> _earth;
	shared_ptr<Quad> _moon;

	shared_ptr<Transform> _earthParent;
	shared_ptr<Transform> _moonParent;
};

