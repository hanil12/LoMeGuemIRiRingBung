#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Spin Lock : ���ѷ����� Ÿ�鼭 �ڹ��� Ǯ�� �� ���� �ݺ�(CAS)
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
		// 1. flag�� expected�� ���� ���Ҵ�. => flag�� desired�� ��ü, true��ȯ
		// 2. flag�� expected�� ���� �޶���. => flag�� expected�� ��ü, false ��ȯ

		while (flag.compare_exchange_strong(expected, desired) == false)
		{
			// flag�� expected�� ���� �޶���.
			// => lock �����ִ�.
			expected = false;
		}

		#pragma region spinLock ���� �� �ܰ�
		//while (flag.load() == true) // t1, t2�� ���ÿ� ���⼭ ����... flag ... false1
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
	// ������ ����ȭ
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