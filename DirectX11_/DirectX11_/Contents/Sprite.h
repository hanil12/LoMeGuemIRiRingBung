#pragma once
#include "Action.h"

class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector maxFrame);
	~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	void SetCurFrame(Vector frame);
	void SetCurFrame(Action::Clip clip);

	Vector MaxFrame() { return _frameBuffer->GetMaxFrame(); }
	Vector CurFrame() { return _frameBuffer->GetCurFrame(); }

private:
	virtual void CreateVertices() override;

	shared_ptr<FrameBuffer> _frameBuffer;
};

