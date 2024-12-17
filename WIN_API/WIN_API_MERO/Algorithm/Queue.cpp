#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// Queue
// - First Input First Out : FIFO

class Queue
{
public:
	void push(const int& value) { l.push_back(value); }
	void pop() { l.pop_front(); }
	int front() { return l.front(); }
	bool empty() { return l.empty(); }

private:
	list<int> l;
};

int main()
{
	queue<int> q;

	q.push(1);
	q.push(5);
	q.push(10);
	q.push(222);
	q.push(3);

	while (true)
	{
		cout << q.front() << endl;

		q.pop();

		if(q.empty() == true)
			break;
	}
}