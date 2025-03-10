#include <mutex>

#include "User.h"
#include "Account.h"

User* User::_instance = nullptr;
void User::Save()
{
	std::lock_guard<std::mutex> lg(_m);

	// Account 확인
	Account::Instance()->GetAccount(0);

	// DB 계정정보를 저장...

	return;
}

int User::GetUser(int id)
{
	std::lock_guard<std::mutex> lg(_m);

	// UserInfo 추출

	return 0;
}
