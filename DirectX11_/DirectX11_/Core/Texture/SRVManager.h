#pragma once
class SRVManager
{
	SRVManager();
	~SRVManager();
public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new SRVManager();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static SRVManager* Instance()
	{
		return _instance;
	}

	shared_ptr<SRV> AddSRV(wstring path);

private:
	static SRVManager* _instance;

	unordered_map<wstring, shared_ptr<SRV>> _srvTable;
};

