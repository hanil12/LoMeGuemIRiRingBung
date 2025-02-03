#pragma once
class StateManager
{
public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new StateManager();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static StateManager* Instance()
	{
		return _instance;
	}

	shared_ptr<SamplerState> GetSamplerState() { return _samplerState; }
	shared_ptr<BlendState> GetAlphaState() { return _alphaState; }
	shared_ptr<BlendState> GetAdditiveState() { return _additiveState; }
	shared_ptr<BlendState> GetNoneBlendState() { return _noneBlendState; }

private:
	StateManager();
	~StateManager();

private:
	static StateManager* _instance;

	shared_ptr<SamplerState>	_samplerState;

	shared_ptr<BlendState>		_alphaState;
	shared_ptr<BlendState>		_additiveState;
	shared_ptr<BlendState>		_noneBlendState;
};

