#pragma once
class Account
{
	Account() {}
	~Account() {}

public:
	static Account* Instance()
	{
		if(_instance == nullptr)
			_instance = new Account();
		return _instance;
	}

	static void Delete()
	{
		if(_instance)
			delete _instance;
	}

	void Login();
	int GetAccount(int id);

private:
	std::mutex _m;
	static Account* _instance;
};

