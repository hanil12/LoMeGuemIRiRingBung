#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>

using namespace std;

queue<int> q;
mutex m;
HANDLE handle;

// Produce And Consume

void Producer()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lock(m);
			q.push(100);
		}

		::SetEvent(handle);
		this_thread::sleep_for(10ms);
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(handle, INFINITE); // 운영체제한테 제어권을 넘겨주는 것
		unique_lock<std::mutex> lock(m);

		if (q.empty() == false)
		{
			int data = q.front();

			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
	// 보안속성, 메뉴얼 리셋, 초기상태
	// 메뉴얼 리셋 : 수동
	handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}