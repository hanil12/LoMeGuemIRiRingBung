#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector maxFrame);
	~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	void SetCurFrame(Vector frame);

private:
	shared_ptr<FrameBuffer> _frameBuffer;
};

