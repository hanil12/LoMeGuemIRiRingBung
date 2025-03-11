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
		::WaitForSingleObject(handle, INFINITE); // �ü������ ������� �Ѱ��ִ� ��
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
	// ���ȼӼ�, �޴��� ����, �ʱ����
	// �޴��� ���� : ����
	handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}