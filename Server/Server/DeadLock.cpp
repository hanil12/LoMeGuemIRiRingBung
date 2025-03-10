#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

#include "Account.h"
#include "User.h"

void Func1()
{
	for (int i = 0; i < 10000; i++)
	{
		User::Instance()->Save();
	}
}

void Func2()
{
	for (int i = 0; i < 10000; i++)
	{
		Account::Instance()->Login();
	}
}

int main()
{
	std::thread t1(Func1);
	std::thread t2(Func2);

	t1.join();
	t2.join();

	Account::Delete();
	User::Delete();

	return 0;
}