#include "framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, string name, Type type, float speed)
: _clips(clips)
, _name(name)
, _repeatType(type)
, _speed(speed)
{
}

Action::~Action()
{
}

void Action::Update()
{
	if(_isPlay == false)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;

		switch (_repeatType)
		{
		case Action::END:
		{
			_curClipIndex++;
			if(_curClipIndex >= _clips.size())
				Stop();
		}
			break;
		case Action::LOOP:
		{
			_curClipIndex++;
			_curClipIndex %= _clips.size();
		}
			break;
		case Action::PINGPONG:
		{
			if (!_isReverse)
			{
				_curClipIndex++;
				if (_curClipIndex >= _clips.size())
				{
					_curClipIndex--;
					_isReverse = true;
				}
			}
			else
			{
				_curClipIndex--;
				if (_curClipIndex < 0)
				{
					_curClipIndex = 0;
					_isReverse = false;
				}
			}
		}
		break;
		default:
			break;
		}
	}
}

void Action::Play()
{
	_isPlay = true;
	_isReverse = false;
	_time = 0.0f;
	_curClipIndex = 0;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Stop()
{
	_isPlay = false;
	_time = 0.0f;
	_curClipIndex = 0;

	if(_event != nullptr)
		_event();
}

void Action::Reset()
{
	_isPlay = true;
	_time = 0.0f;
	_curClipIndex = 0;
}
