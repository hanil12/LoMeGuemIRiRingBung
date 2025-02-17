#include "framework.h"
#include "TimeManager.h"

TimeManager* TimeManager::_instance = nullptr;

TimeManager::TimeManager()
{
	QueryPerformanceFrequency((LARGE_INTEGER*) &_periodFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*) &_lastTime);

	_timeScale = 1.0 / (double)_periodFrequency;
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_deltaTime = (double)(_curTime - _lastTime) * _timeScale; // scale�� 0�̵Ǹ� ����, scale�� �����Ǹ� ��������.

	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_deltaTime = (double)(_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	if (_oneSecCount > 1)
	{
		_oneSecCount = 0;
		_frameRate = _frameCount;
		// FPS
		_frameCount = 0;
	}

	// ���� ���α׷��� �����ϰ� �帥 �ð�
	_runTime += _deltaTime;
}
