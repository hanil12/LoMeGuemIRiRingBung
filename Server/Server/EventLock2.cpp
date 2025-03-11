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

// 1. Event��� Lock ... Window�Լ��� ���� ������ ������ȯ�濡�� ȣȯ�� ���� �ʴ´�.
// => CV (condition variable)
// ... Consumer...������ �ɰ� ������ ���� ���� ���� �ɾ���� ����
// => ��Ƽ������ ȯ�濡�� Sleep�� ��Ű�� ������ Producer�� ������ ���� �ʰ� �����ϱ� ������ �ùٸ��� �������� ���� ���� �ִ�.

// => ���ü��� ���� �� Produce�� ���� ���� �ִ�.

// Produce And Consume ����

void Producer()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lock(m);
			q.push(100);
		}

		// wait ���� thread�� ������ �� 1���� �����.
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
		// ���Ǻ����� ��ٸ��� �ִٰ� ������ ���� ��
		// -> q�� ������� ������, lock ����

		int data = q.front();

		q.pop();
		cout << q.size() << endl;
	}
}

int main()
{
	// ���ȼӼ�, �޴��� ����, �ʱ����
	// �޴��� ���� : ����
	//handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}