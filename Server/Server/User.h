#pragma once
class User
{
	User() {}
	~User() {}

public:
	static User* Instance() 
	{ 
		if (_instance == nullptr)
		{
			_instance = new User();
		}

		return _instance;
	}

	static void Delete()
	{
		if(_instance)
			delete _instance;
	}

	void Save();
	int GetUser(int id);

private:
	std::mutex _m;
	static User* _instance;
};

