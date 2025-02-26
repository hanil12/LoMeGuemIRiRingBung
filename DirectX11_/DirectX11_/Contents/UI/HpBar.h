#pragma once
class HpBar
{
public:
	HpBar(Vector center, Vector size);
	~HpBar();

	void Update();
	void Render();

	void SetPosition(Vector pos);
	void SetSize(Vector size);

	void SetRatio(float value) { /*TODO*/};

private:
	float value = 1.0f;

	shared_ptr<Quad> _hpBar;
	shared_ptr<Quad> _bg;

	shared_ptr<SliderBuffer> _sliderBuffer;
};

