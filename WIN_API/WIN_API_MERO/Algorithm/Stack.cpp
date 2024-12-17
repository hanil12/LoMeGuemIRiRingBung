#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// stack 구조
// - First Input Last Output : FILO
// - Last Input First Output : LIFO
// => 팬케이크

// data형은 T형
template<typename T, typename Container = vector<int>>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_back();
	}

	T top()
	{
		return _container.back();
	}

	bool empty()
	{
		return _container.size() == 0;
	}

private:
	Container _container;
};

int main()
{
	stack<int,vector<int>> s;

	s.push(1);
	s.push(5);
	s.push(10);
	s.push(222);
	s.push(3);

	while (true)
	{
		cout << s.top() << endl;
		s.pop();

		if(s.empty() == true)
			break;
	}


	return 0;
}