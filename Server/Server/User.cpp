#include <mutex>

#include "User.h"
#include "Account.h"

User* User::_instance = nullptr;
void User::Save()
{
	std::lock_guard<std::mutex> lg(_m);

	// Account Ȯ��
	Account::Instance()->GetAccount(0);

	// DB ���������� ����...

	return;
}

int User::GetUser(int id)
{
	std::lock_guard<std::mutex> lg(_m);

	// UserInfo ����

	return 0;
}
