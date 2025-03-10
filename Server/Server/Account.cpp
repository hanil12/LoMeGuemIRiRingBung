#include <mutex>

#include "Account.h"
#include "User.h"

Account* Account::_instance = nullptr;
void Account::Login()
{
    std::lock_guard<std::mutex> lg(_m);

    // User 정보를 뽑기
    User::Instance()->GetUser(0);

    return;
}

int Account::GetAccount(int id)
{
    std::lock_guard<std::mutex> lg(_m);

    // Account정보를 DB에서 갖고 오기

    return 0;
}
