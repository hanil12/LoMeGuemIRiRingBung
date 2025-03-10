#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Spin Lock : 무한루프를 타면서 자물쇠 풀릴 때 까지 반복(CAS)
// Sleep Lock
// Event Lock

class SpinLock
{
public:
	void lock()
	{
		// CAS : Compare And Swap 
		bool expected = false;
		bool desired = true;
		// compare_exchange_strong
		// 1. flag가 expected와 서로 같았다. => flag는 desired로 교체, true반환
		// 2. flag가 expected와 서로 달랐다. => flag는 expected로 교체, false 반환

		while (flag.compare_exchange_strong(expected, desired) == false)
		{
			// flag와 expected가 서로 달랐다.
			// => lock 잡혀있다.
			expected = false;
		}

		#pragma region spinLock 구현 전 단계
		//while (flag.load() == true) // t1, t2가 동시에 여기서 경합... flag ... false1
		//{
		//}

		//flag.store(true); // flag ... true
		#pragma endreigon
	}

	void unlock()
	{
		flag.store(false);
	}

private:
	// 컴파일 최적화
	atomic<bool> flag = false;
};

int sum = 0;
std::mutex m;
SpinLock myMutex;

void Add()
{
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<SpinLock> lg(myMutex); // t1 ... flag ...true
		sum++;
	}
	// flag... false
}

void Sub()
{
	for (int i = 0; i < 100000; i++)
	{
		lock_guard<SpinLock> lg(myMutex); // t2
		sum--;
	}
}

int main()
{
	//atomic<bool> temp = true;

	//while (temp)
	//{

	//}

	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;

	return 0;
}