#include <mutex>

#include "Account.h"
#include "User.h"

Account* Account::_instance = nullptr;
void Account::Login()
{
    std::lock_guard<std::mutex> lg(_m);

    // User ������ �̱�
    User::Instance()->GetUser(0);

    return;
}

int Account::GetAccount(int id)
{
    std::lock_guard<std::mutex> lg(_m);

    // Account������ DB���� ���� ����

    return 0;
}
