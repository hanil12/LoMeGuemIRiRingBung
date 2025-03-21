#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(Data))
	{
	}
	~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		_data.matrix = XMMatrixTranspose(value);
	}

private:
	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer()
	: ConstantBuffer(&_data, sizeof(Data))
	{
	}
	~ColorBuffer() {}

	void SetData(XMFLOAT4 value)
	{
		_data.color = value;
	}

private:
	Data _data;
};

class FlipBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int leftRight = 0;
		int padding[3];
	};

	FlipBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
	~FlipBuffer() {}

	void SetData(int leftRight)
	{
		_data.leftRight = leftRight;
	}

private:
	Data _data;
};

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 maxFrame;
		XMFLOAT2 curFrame;
	};

	FrameBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
	~FrameBuffer() {}

	void SetMaxFrame(XMFLOAT2 value)
	{
		_data.maxFrame = value;
	}
	void SetCurFrame(XMFLOAT2 value)
	{
		_data.curFrame = value;
	}

	Vector GetMaxFrame() { return Vector(_data.maxFrame); }
	Vector GetCurFrame() { return Vector(_data.curFrame); }

private:
	Data _data;
};


class SliderBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		float sliderValue = 0.0f;
		int padding[3];
	};

	SliderBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
	}
	~SliderBuffer() {}

	void SetData(float value)
	{
		_data.sliderValue = value;
	}

private:
	Data _data;
};