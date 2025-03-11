#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>

using namespace std;

queue<int> q;
mutex m;
// HANDLE handle;
condition_variable cv;

// 1. Event기반 Lock ... Window함수를 쓰기 때문에 리눅스환경에서 호환이 되지 않는다.
// => CV (condition variable)
// ... Consumer...조건을 걸고 조건이 참일 때만 락을 걸어잠고 진행
// => 멀티쓰레드 환경에서 Sleep을 시키지 않으면 Producer는 조건을 보지 않고 생성하기 때문에 올바르게 동작하지 않을 수도 있다.

// => 동시성이 생길 때 Produce를 더할 수도 있다.

// Produce And Consume 패턴

void Producer()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lock(m);
			q.push(100);
		}

		// wait 중인 thread가 있으면 딱 1개를 깨운다.
		cv.notify_one();
		this_thread::sleep_for(10ms);
	}
}

void Consumer()
{
	while (true)
	{
		unique_lock<std::mutex> lock(m);
		cv.wait(lock, []() -> bool { return q.empty() == false; }); 
		// 조건변수가 기다리고 있다가 통지가 왔을 때
		// -> q가 비어있지 않으면, lock 해제

		int data = q.front();

		q.pop();
		cout << q.size() << endl;
	}
}

int main()
{
	// 보안속성, 메뉴얼 리셋, 초기상태
	// 메뉴얼 리셋 : 수동
	//handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}