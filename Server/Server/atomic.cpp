#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Process : 메모리 상에 존재하는 실행중인 프로그램
// Thread : Process 내에서 작업의 단위

// CPU 코어 : CPU내에서 실제 연산을 수행하는 단위

// 멀티쓰레드와 멀티태스킹 : 

// atomic : 원자적인
// lock : 자물쇠

atomic<int> sum = 0;

void AddSum()
{
	for (int i = 0; i < 10000; i++)
	{
		sum.fetch_add(1);
	}
}

void SubSum()
{
	for (int i = 0; i < 10000; i++)
	{
		sum.fetch_sub(1);
	}
}

int main()
{
	vector<std::thread> threads;
	threads.resize(10);

	for (int i = 0; i < 5; i++)
	{
		threads[i] = std::thread(AddSum);
	}

	for (int i = 5; i < 10; i++)
	{
		threads[i] = std::thread(SubSum);
	}

	for(int i=0;i<10;i++)
		threads[i].join();

	cout << sum << endl;

	return 0;
}