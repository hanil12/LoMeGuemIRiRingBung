#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Sleep Lock
// Context Switching


class SleepLock
{
public:
	void lock()
	{
		bool expected = false;
		bool desired = true;

		while (flag.compare_exchange_strong(expected, desired) == false)
		{
			expected = false;
			this_thread::sleep_for(std::chrono::seconds(3));
		}
#pragma endreigon
	}

	void unlock()
	{
		flag.store(false);
	}

private:

	atomic<bool> flag = false;
};

int sum = 0;
std::mutex m;
SleepLock myMutex;

void Add()
{
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<SleepLock> lg(myMutex);
		sum++;
	}
}

void Sub()
{
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<SleepLock> lg(myMutex);
		sum--;
	}
}

int main()
{

	std::thread t1(Add);
	std::thread t2(Sub);
	std::thread t3(Add);
	std::thread t4(Sub);
	std::thread t5(Add);
	std::thread t6(Sub);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	cout << sum << endl;

	return 0;
}