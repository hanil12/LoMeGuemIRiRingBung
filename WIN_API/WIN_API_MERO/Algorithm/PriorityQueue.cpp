#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// 완전이진트리 => vector로 구현할 수 있다.
template<typename T, typename Container = vector<T>, typename Pred = less<T>>
class Priority_Queue
{
public:
	// 123 3 12 1  ... 55 push
	void push(const T& value)
	{
		container.push_back(value);

		// 123 3 12 1 55 
		int nowIndex = container.size() - 1;
		// nowIndex = 4

		while (true)
		{
			if(nowIndex <= 0)
				break;

			int parentIndex = (nowIndex - 1) / 2; // 부모인덱스 찾기
			//if(container[parentIndex] > container[nowIndex]) // 부모가 나보다 크거나 같다 => 힙트리 원칙에 부합한다.
			if(pred(container[nowIndex], container[parentIndex]))
				break;

			// Swap
			std::swap(container[nowIndex], container[parentIndex]);
			nowIndex = parentIndex;
		}
	}

	void pop()
	{
		// std::swap(v[0], v[v.size() - 1]);
		container[0] = container.back();

		container.pop_back();

		int nowIndex = 0;
		while (true)
		{
			int leftChild = nowIndex * 2 + 1;
			int rightChild = nowIndex * 2 + 2;

			// 탈출 조건 : 자식이 없는 경우
			if(leftChild >= container.size())
				break;
			
			int next = nowIndex;
			if (pred(container[next], container[leftChild]))
			{
				next = leftChild;
			}
			if (rightChild < container.size() && pred(container[next], container[rightChild]))
			{
				next = rightChild;
			}

			if(nowIndex == next)
				break;

			//next는 부모 자식 두명 사이에서 최대값을 가진 Index
			std::swap(container[nowIndex], container[next]);
			nowIndex = next;
		}

	}

	int top()
	{
		return container[0];
	}

	bool empty()
	{
		return container.empty();
	}

private:
	Pred pred;
	Container container;
};

int main()
{
	Priority_Queue<int, vector<int>, greater<int>> pq;

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