#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// 완전이진트리 => vector로 구현할 수 있다.
class Priority_Queue
{
public:
	// 123 3 12 1  ... 55 push
	void push(const int& value)
	{
		v.push_back(value);

		// 123 3 12 1 55 
		int nowIndex = v.size() - 1;
		// nowIndex = 4

		while (true)
		{
			if(nowIndex <= 0)
				break;

			int parentIndex = (nowIndex - 1) / 2; // 부모인덱스 찾기
			if(v[parentIndex] >= v[nowIndex]) // 부모가 나보다 크거나 같다 => 힙트리 원칙에 부합한다.
				break;

			// Swap
			std::swap(v[nowIndex], v[parentIndex]);
			nowIndex = parentIndex;
		}
	}

	void pop()
	{

	}

	int top()
	{
		return -1;
	}

	bool empty()
	{
		return v.empty();
	}

private:
	vector<int> v;
};

int main()
{
	priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(123);
	pq.push(1);
	pq.push(12);
	pq.push(3);
	pq.push(55);
	pq.push(150);
	pq.push(6);

	while (true)
	{
		if(pq.empty()) break;

		int top = pq.top();

		cout << top << endl;
		pq.pop();
	}

	return 0;
}