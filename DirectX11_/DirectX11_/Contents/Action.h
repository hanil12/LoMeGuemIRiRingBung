#pragma once
class Action
{
public:
	struct Clip
	{
		Vector startPos;
		Vector size;
		weak_ptr<SRV> srv;

		Clip(float x, float y, float w, float h, shared_ptr<SRV> srv)
			: startPos(x, y), size(w, h), srv(srv)
		{

		}
	};

	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

	Action(vector<Clip> clips, string name = "", Type type = END, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	Clip GetCurClip() { return _clips[_curClipIndex]; }
	Action::Type GetRepeatType() { return _repeatType; }
	bool IsPlay() { return _isPlay; }

	void SetCallBack(function<void(void)> func) { _event = func; }

private:
	vector<Clip>			_clips;
	string					_name;
	Type					_repeatType;
	float					_speed;

	bool					_isPlay = false;
	bool					_isReverse = false;
	UINT					_curClipIndex = 0;
	float					_time = 0.0f;

	function<void(void)>	_event = nullptr;
};

