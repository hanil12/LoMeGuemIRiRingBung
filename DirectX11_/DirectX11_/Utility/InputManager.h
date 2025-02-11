#pragma once

#define KEY_MAX 255

class InputManager
{
private:
	enum State
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InputManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return _instance;
	}

	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

private:
	static InputManager* _instance;

	byte _curState[KEY_MAX]; // 'W' = 250
	byte _oldState[KEY_MAX]; // _oldState[250] = 0
	byte _stateMap[KEY_MAX]; // _stateMap[250] NONE;
};

