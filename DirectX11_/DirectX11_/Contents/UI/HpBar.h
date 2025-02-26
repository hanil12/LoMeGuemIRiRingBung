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

	void SetRatio(float value) { _sliderBuffer->SetData(value); _value = value; _sliderBuffer->Update(); }

private:
	float _value = 1.0f;

	shared_ptr<Quad> _hpBar;
	shared_ptr<Quad> _bg;

	shared_ptr<SliderBuffer> _sliderBuffer;
};

