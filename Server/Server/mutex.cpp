#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// mutex : mutual exclusion => 상호배제
// lock 
// RAII : Resource Acquisition is initialization

vector<int> v;
std::mutex m; // 자물쇠

template <typename T>
class LockGuard
{
public:
	LockGuard(T* mutex) : _mutex(mutex) { _mutex->lock(); }
	~LockGuard() { _mutex->unlock(); }

private:
	T* _mutex;
};

void Push(int count)
{
	LockGuard<std::mutex> lg(&m);
	//m.lock();

	for (int i = 0; i < count; i++)
	{
		v.push_back(1);
	}

	//m.unlock();
}

int main()
{
	vector<std::thread> threads;
	threads.resize(10);

	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(Push,1000);
	}

	for(int i=0;i<10;i++)
		threads[i].join();

	cout << v.size() << endl;

	return 0;
}